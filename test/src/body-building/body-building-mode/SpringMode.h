#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <memory>
#include <Option.h>

/// @brief 弹簧模式
class SpringMode : public base::IExecutable
{
private:
    /// @brief 放线 1m 对应的伺服反馈位置。
    /// @return
    int OneMeterPosition()
    {
        return 10000;
    }

    /// @brief 弹簧弹性系数。
    /// @return
    double Ratio()
    {
        return 1.5;
    }

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            base::InertialElement_TimeConstant{0.025},
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
