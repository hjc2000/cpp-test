#pragma once
#include <base/IExecutable.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <Option.h>

class StandardMode :
    public base::IExecutable
{
private:
    std::shared_ptr<Cmd> _cmd;

    base::LinearInterpolator _tension_linear_interpolator{
        base::LinearInterpolator_StartVlaue{0},
        base::LinearInterpolator_EndVlaue{Option::Instance().Tension_kg()},
        base::LinearInterpolator_StepLength{0.03},
    };

public:
    StandardMode(std::shared_ptr<Cmd> cmd)
    {
        _cmd = cmd;
    }

    void Execute();
};
