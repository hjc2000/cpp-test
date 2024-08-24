#include "StandardMode.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void StandardMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());
    if (Option::Instance().Tension_kg_Changed())
    {
        _tension_linear_interpolator.SetEndValue(Option::Instance().Tension_kg());
    }

    double tension = ++_tension_linear_interpolator;
    if (tension < 4)
    {
        tension = 4;
    }

    int torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
