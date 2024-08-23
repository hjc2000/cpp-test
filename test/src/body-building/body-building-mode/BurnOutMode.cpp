#include "BurnOutMode.h"
#include <base/math/InertialElement.h>
#include <ChXFilter.h>
#include <Cmd.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

void BurnOutMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
    }

    if (Servo::Instance().FeedbackSpeed() > 10)
    {
        _burn_out_tick++;
    }
}
