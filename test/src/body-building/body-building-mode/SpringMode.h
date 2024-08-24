#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>
#include <Option.h>

class ISpringMode_InfomationGetter
{
public:
    virtual double Tension_kg() = 0;
    virtual double TorqueRatio() = 0;
    virtual int OneMeterPosition() = 0;
    virtual int FeedbackPosition() = 0;

    /// @brief 弹簧劲度系数。
    /// @return
    virtual double SpringRatio() = 0;
};

/// @brief 弹簧模式
class SpringMode :
    public base::IExecutable
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

    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<ISpringMode_InfomationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            base::InertialElement_TimeConstant{0.025},
            base::InertialElement_SampleInterval{0.002},
        },
    };

public:
    SpringMode(std::shared_ptr<Cmd> cmd,
               std::shared_ptr<ISpringMode_InfomationGetter> infos)
    {
        _cmd = cmd;
        _infos = infos;

        _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
            new base::LinearInterpolator{
                base::LinearInterpolator_StartVlaue{0},
                base::LinearInterpolator_EndVlaue{_infos->Tension_kg()},
                base::LinearInterpolator_StepLength{0.03},
            },
        };
    }

    void Execute() override;
};
