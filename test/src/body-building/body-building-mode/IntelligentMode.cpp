#include "IntelligentMode.h"
#include <cmath>
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void IntelligentMode::Execute()
{
    if (Servo::Instance().FeedbackSpeed() > 10)
    {
        double feedback_speed = Servo::Instance().FeedbackSpeed();
        if (feedback_speed > 3500)
        {
            feedback_speed = 3500;
        }

        double torque = (1 - std::cos(feedback_speed / 3500 * 3.14159)) / 2 * k() + b();
        if (torque > _filter->CurrentOutput())
        {
            _filter->ChangeParameter(_little_time_constant);
        }
        else
        {
            _filter->ChangeParameter(_big_time_constant);
        }

        _filter->Input(torque);
        _cmd->SetSpeed(0);
    }
    else
    {
        _filter->SetCurrentOutput(SRV_PARA(1, 34));
        _cmd->SetSpeed(Option::Instance().WindingSpeed());
    }

    double torque = _filter->CurrentOutput();
    if (torque < 10)
    {
        torque = 10;
    }
    else if (torque > Option::Instance().MaxTorque())
    {
        torque = Option::Instance().MaxTorque();
    }

    _cmd->SetTorque(torque);
}
