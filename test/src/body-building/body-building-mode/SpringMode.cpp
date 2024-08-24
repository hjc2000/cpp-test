#include "SpringMode.h"
#include <Cmd.h>

void SpringMode::Execute()
{
    _cmd->SetSpeed(_infos->Option_WindingSpeed_rpm());
    _current_tension_kg = _infos->Option_Tension_kg();
    if (_last_tension_kg != _current_tension_kg)
    {
        _tension_linear_interpolator->SetEndValue(_current_tension_kg);

        _filter = std::shared_ptr<base::ChXFilter>{
            new base::ChXFilter{
                base::ChXFilter_KError{10},
                base::ChXFilter_FeedbackDiv{40},
            },
        };
    }

    double tension = ++(*_tension_linear_interpolator);
    double torque = tension * _infos->Option_TorqueRatio();

    if (_infos->Servo_FeedbackPosition() < _infos->Option_OneMeterPosition())
    {
        torque = torque * _infos->Servo_FeedbackPosition() / _infos->Option_OneMeterPosition();
    }
    else
    {
        int delta_position = _infos->Servo_FeedbackPosition() - _infos->Option_OneMeterPosition();
        torque = torque + (delta_position * _infos->Option_SpringRatio() / 30000);
    }

    torque = _filter->Input(torque);
    if (torque < 5)
    {
        torque = 5;
    }

    _cmd->SetTorque(torque);
}
