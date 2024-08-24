#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <ChXFilter.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>

class IntelligentMode : public base::IExecutable
{
private:
    double k()
    {
        return SRV_PARA(1, 45) / 100;
    }

    double b()
    {
        return SRV_PARA(1, 46) / 100;
    }

    base::InertialElement_TimeConstant const _little_time_constant{CalculateTimeConstant(5, 10000)};
    base::InertialElement_TimeConstant const _big_time_constant{CalculateTimeConstant(500, 10000)};

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            _little_time_constant,
            base::InertialElement_SampleInterval{0.002},
        },
    };

    base::LinearInterpolator _tension_linear_interpolator{
        base::LinearInterpolator_StartVlaue{0},
        base::LinearInterpolator_EndVlaue{Option::Instance().Tension_kg()},
        base::LinearInterpolator_StepLength{0.03},
    };

public:
    void Execute();
};
