#include "AssistanceMode.h"
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
#include <State.h>
#include <TensionLinearInterpolator.h>

void AssistanceMode::OnFromUnwindingToWinding()
{
}

void AssistanceMode::OnFromWindingToUnwinding()
{
}

double AssistanceMode::CalSubKg(double base_kg)
{
    double zlSubkg = (base_kg * 5 + 15) * 0.2;
    double zlSubkgV = static_cast<int>(zlSubkg / 5) * 5;
    if (zlSubkg - zlSubkgV > 0)
    {
        zlSubkgV = zlSubkgV + 5;
    }

    return zlSubkgV * 0.2;
}

void AssistanceMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged())
    {
        PullTimesDetector::Instance().Reset();
        _tension = Option::Instance().Tension_kg();
    }

    if (Servo::Instance().FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    if (PullTimesDetector::Instance().UnwindingTimesChanged())
    {
        // 经历了有效放线
        _has_effective_unwinding = true;
    }
    else if (PullTimesDetector::Instance().WindingTimesChanged())
    {
        // 经历了有效收线
        _has_effective_winding = true;
    }

    if (DI_DirectionDetecter().DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
    {
        // 从放线变成收线
        if (_has_effective_unwinding)
        {
            _has_effective_unwinding = false;
            OnFromUnwindingToWinding();
        }
    }
    else if (DI_DirectionDetecter().DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
    {
        // 从收线变成放线
        if (_has_effective_winding)
        {
            _has_effective_winding = false;
            OnFromWindingToUnwinding();
        }
    }

    DD(14, _tension * 5 + 15);
    double torque = _tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
