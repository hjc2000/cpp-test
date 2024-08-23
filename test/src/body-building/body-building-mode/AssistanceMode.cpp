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
    if (PullTimesDetector::Instance().UnwindingTimes() < 2)
    {
        _zlSub = false;
        _zlTrigger = false;
        _tension = Option::Instance().Tension_kg();
    }
    else if (PullTimesDetector::Instance().UnwindingTimes() == 2)
    {
        _zlDist1 = PullLengthDetecter::Instance().PullLength();
        _zlTim1 = _unwinding_tick;
    }
    else if (PullTimesDetector::Instance().UnwindingTimes() == 3)
    {
        _zlDist2 = PullLengthDetecter::Instance().PullLength();
        _zlTim2 = _unwinding_tick;
        _zlDistBase = (_zlDist1 + _zlDist2) / 2 * 0.9;
        _zlTimBase = (_zlTim1 + _zlTim2) / 2 + 500;
    }

    _zlTrigger = false;
    _needChk = false;
}

void AssistanceMode::OnFromWindingToUnwinding()
{
    _needChk = true;
    if (Servo::Instance().FeedbackPosition() < Option::Instance().ZeroPositionProtectionThreshold())
    {
        if (_needChk && !State::Instance().IsTurningForward())
        {
            _needChk = 0;
        }

        if (PullTimesDetector::Instance().WindingTimes() > 3)
        {
            if (_tension <= 1)
            {
                _needChk = false;
                _tension = 1;
                _zlTrigger = false;
            }

            if (PullTimesDetector::Instance().UnwindingTimes() > _zlTimBase)
            {
                if (PullLengthDetecter::Instance().LastPullLength() < _zlTimBase && _needChk == 1)
                {
                    _zlTrigger = true;
                }
                else
                {
                    _needChk = false;
                    _zlTrigger = false;
                }
            }
        }

        if (_zlTrigger)
        {
            _zlSubCnt++;
        }
        else
        {
            _zlSubCnt = 0;
        }

        if (_zlSubCnt == 1)
        {
            if (_zlSub)
            {
                _zlTrqBase = _zlTrqBase - _zlSubTrq;
            }
            else
            {
                _zlSub = true;
                _zlTrqBase = _tension;
            }

            _zlSubTrqCnt = 0;
        }
    }
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
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
        PullTimesDetector::Instance().Reset();
        _zlSub = false;
        _tension = Option::Instance().Tension_kg();
        _zlTrigger = false;
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
            OnFromWindingToUnwinding();
        }
    }

    DD(14, _tension * 5 + 15);
    double tension = TensionLinearInterpolator::Instance().StepForward();
    double torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
