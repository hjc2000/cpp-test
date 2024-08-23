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
#include <TensionLinearInterpolator.h>

void AssistanceMode::OnFromUnwindingToWinding()
{
}

void AssistanceMode::OnFromWindingToWinding()
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

    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
        PullTimesDetector::Instance().Reset();
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

    if (DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromUnwindingToWinding)
    {
        // 从放线变成收线
        if (_has_effective_unwinding)
        {
            _has_effective_unwinding = false;
            OnFromUnwindingToWinding();
        }
    }
    else if (DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromWindingToUnwinding)
    {
        // 从收线变成放线
        if (_has_effective_winding)
        {
            _has_effective_winding = false;
            OnFromWindingToWinding();
        }
    }

    DD(14, _tension * 5 + 15);
    double tension = TensionLinearInterpolator::Instance().StepForward();
    double torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
