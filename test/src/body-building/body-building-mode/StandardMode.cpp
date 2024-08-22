#include "StandardMode.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

void StandardMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());
    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
    }

    double tension = TensionLinearInterpolator::Instance().StepForward();
    int torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
