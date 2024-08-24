#pragma once
#include <base/IExecutable.h>
#include <base/math/LinearInterpolator.h>
#include <Option.h>

class StandardMode :
    public base::IExecutable
{
private:
    base::LinearInterpolator _tension_linear_interpolator{
        0,
        Option::Instance().Tension_kg(),
        base::LinearInterpolator_StepLength{1.5},
    };

public:
    void Execute();
};
