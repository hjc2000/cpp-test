#include "BurnOutMode.h"
#include <base/math/InertialElement.h>
#include <ChXFilter.h>
#include <Cmd.h>
#include <DirectionDetector.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>
#include <PullLengthDetecter.h>
#include <PullTimesDetector.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

void BurnOutMode::OnFromUnwindingToWinding()
{
    if (PullTimesDetector::Instance().UnwindingTimes() < 2)
    {
        // 被拉出次数小于 2
        _t2 = 0;
        _t3 = 0;
        _changing = false;
        _tension = Option::Instance().Tension_kg();
    }
    else if (PullTimesDetector::Instance().UnwindingTimes() == 2)
    {
        _tension = Option::Instance().Tension_kg();
        _t2 = _tension * PullLengthDetecter::Instance().PullLength() / _burn_out_tick;
        _last_pull_length = PullLengthDetecter::Instance().PullLength();
    }
    else if (PullTimesDetector::Instance().UnwindingTimes() == 3)
    {
        _last_pull_length = (_last_pull_length + PullLengthDetecter::Instance().PullLength()) / 2;
        _t3 = _tension * PullLengthDetecter::Instance().PullLength() / _burn_out_tick;
        _burn_out_power = (_t2 + _t3) / 2;
    }
    else
    {
    }
}

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

    if (DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromUnwindingToWinding)
    {
        // 从放线变成收线
        OnFromUnwindingToWinding();
    }
}
