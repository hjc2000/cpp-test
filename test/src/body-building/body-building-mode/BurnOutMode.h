#pragma once
#include <base/IExecutable.h>
#include <base/math/DirectionDetecter.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>
#include <Option.h>
#include <PullTimesDetector.h>

class BurnOutMode :
    public base::IExecutable
{
private:
    int _unwinding_tick = 0;
    double _t2 = 0;
    double _t3 = 0;
    bool _changing = false;
    double _tension = 0;
    int _last_pull_length = 0;
    double _power = 0;
    std::shared_ptr<Cmd> _cmd;
    PullTimesDetector _pull_times_detecter;

    base::LinearInterpolator _tension_linear_interpolator{
        base::LinearInterpolator_StartVlaue{0},
        base::LinearInterpolator_EndVlaue{Option::Instance().Tension_kg()},
        base::LinearInterpolator_StepLength{0.03},
    };

    void OnFromUnwindingToWinding();

public:
    BurnOutMode(std::shared_ptr<Cmd> cmd)
    {
        _cmd = cmd;
    }

    void Execute();
};
