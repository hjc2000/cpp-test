#pragma once
#include <base/IExecutable.h>
#include <base/math/LinearInterpolator.h>
#include <Option.h>

class StandardMode :
    public base::IExecutable
{
private:
    base::LinearInterpolator _tension_linear_interpolator{
        base::LinearInterpolator_StartVlaue{0},
        base::LinearInterpolator_EndVlaue{Option::Instance().Tension_kg()},
        base::LinearInterpolator_StepLength{0.03},
    };

public:
    void Execute();
};
