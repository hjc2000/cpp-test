#include "StandardMode.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void StandardMode::Execute()
{
    _cmd->SetSpeed(_infos->WindingSpeed_rpm());
    _current_tension_kg = _infos->Tension_kg();
    if (_last_tension_kg != _current_tension_kg)
    {
        _last_tension_kg = _current_tension_kg;
        _tension_linear_interpolator->SetEndValue(_current_tension_kg);
    }

    double tension = ++(*_tension_linear_interpolator);
    if (tension < 4)
    {
        tension = 4;
    }

    int torque = tension * Option::Instance().TorqueRatio();
    _cmd->SetTorque(torque);
}
