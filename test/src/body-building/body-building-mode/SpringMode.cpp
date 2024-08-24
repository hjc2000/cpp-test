#include "SpringMode.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void SpringMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        _tension_linear_interpolator.SetEndValue(Option::Instance().Tension_kg());

        _filter = std::shared_ptr<base::InertialElement>{
            new base::InertialElement{
                base::InertialElement_TimeConstant{0.025},
                base::InertialElement_SampleInterval{0.002},
            },
        };
    }

    double tension = ++_tension_linear_interpolator;
    double torque = tension * Option::Instance().TorqueRatio();

    if (Servo::Instance().FeedbackPosition() < OneMeterPosition())
    {
        torque = torque * Servo::Instance().FeedbackPosition() / OneMeterPosition();
    }
    else
    {
        int delta_position = Servo::Instance().FeedbackPosition() - OneMeterPosition();
        torque = torque + (delta_position * Ratio() / 30000);
    }

    torque = _filter->Input(torque);
    if (torque < 5)
    {
        torque = 5;
    }

    Cmd::Instance().SetTorque(torque);
}
