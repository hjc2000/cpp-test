#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>

/// @brief 向心模式
class CentripetalMode :
    public base::IExecutable
{
private:
    /// @brief 大于 1 的值。
    /// @note 向心模式下，顺从它向心，拉力会减小。减小拉力是通过将转矩除以本系数。
    /// @return
    double Ratio()
    {
        return SRV_PARA(1, 43);
    }

    std::shared_ptr<Cmd> _cmd;

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
    CentripetalMode(std::shared_ptr<Cmd> cmd)
    {
        _cmd = cmd;
    }

    void Execute();
};
