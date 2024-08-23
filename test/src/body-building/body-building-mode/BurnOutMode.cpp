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
        _t2 = _tension * PullLengthDetecter::Instance().PullLength() / _unwinding_tick;
        _last_pull_length = PullLengthDetecter::Instance().PullLength();
    }
    else if (PullTimesDetector::Instance().UnwindingTimes() == 3)
    {
        _last_pull_length = (_last_pull_length + PullLengthDetecter::Instance().PullLength()) / 2;
        _t3 = _tension * PullLengthDetecter::Instance().PullLength() / _unwinding_tick;
        _power = (_t2 + _t3) / 2;
    }
    else
    {
        double ratio = PullLengthDetecter::Instance().PullLength() / _last_pull_length;
        if (_changing)
        {
            ratio = 1;
        }

        double pt = 0;
        if (ratio < 0.7)
        {
            pt = _tension * PullLengthDetecter::Instance().PullLength() / _unwinding_tick * ratio;
        }
        else
        {
            pt = _tension * PullLengthDetecter::Instance().PullLength() / _unwinding_tick;
        }

        double pe_ratio = (pt - _power) / _power;
        double set_kg = _tension * 5 + 15;
        int chg_kg = (set_kg - 1) / 100;

        if (_changing)
        {
            _power = pt;
            _changing = false;
        }
        else
        {
            if (pe_ratio > 0.2 && pe_ratio < 0.5)
            {
                _tension = set_kg + chg_kg * 10 + 10;
                _changing = true;
            }
            else if (pe_ratio > 0.5)
            {
                _tension = set_kg + chg_kg * 10 + 20;
                _changing = true;
            }
            else if (pe_ratio < -0.2 && pe_ratio > -0.5)
            {
                _tension = set_kg - chg_kg * 10 - 10;
                _changing = true;
            }
            else if (pe_ratio < -0.5)
            {
                _tension = set_kg - chg_kg * 10 - 20;
                _changing = true;
            }
            else
            {
                _tension = set_kg;
            }

            if (_tension < 20)
            {
                _tension = 20;
            }
            else if (_tension > Option::Instance().MaxTension_kg())
            {
                _tension = Option::Instance().MaxTension_kg();
            }

            _tension = (_tension - 15) / 5;
        }
    }

    TensionLinearInterpolator::Instance().ChangeEndValue(_tension);
    _unwinding_tick = 0;
}

void BurnOutMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
        PullTimesDetector::Instance().Reset();
        _tension = Option::Instance().Tension_kg();
    }

    if (Servo::Instance().FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    if (PullTimesDetector::Instance().UnwindingTimesChanged())
    {
        // 经过了有效放线s
        _has_effective_unwinding = true;
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

    DD(8, (_tension * 5 + 15));
    double tension = TensionLinearInterpolator::Instance().StepForward();
    double torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
