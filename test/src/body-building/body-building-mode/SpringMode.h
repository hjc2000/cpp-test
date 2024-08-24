#pragma once
#include <base/IExecutable.h>
#include <base/math/ChXFilter.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>

class ISpringMode_InfomationGetter
{
public:
    virtual double Option_Tension_kg() = 0;
    virtual double Option_TorqueRatio() = 0;
    virtual double Option_WindingSpeed_rpm() = 0;
    virtual int Option_OneMeterPosition() = 0;

    /// @brief 弹簧劲度系数。
    /// @return
    virtual double Option_SpringRatio() = 0;

    virtual int Servo_FeedbackPosition() = 0;
};

/// @brief 弹簧模式
class SpringMode :
    public base::IExecutable
{
private:
    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<ISpringMode_InfomationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;
    double _current_tension_kg = 0;
    double _last_tension_kg = 0;

    std::shared_ptr<base::ChXFilter> _filter{
        new base::ChXFilter{
            base::ChXFilter_KError{10},
            base::ChXFilter_FeedbackDiv{40},
        },
    };

public:
    SpringMode(std::shared_ptr<Cmd> cmd,
               std::shared_ptr<ISpringMode_InfomationGetter> infos)
    {
        _cmd = cmd;
        _infos = infos;
        _current_tension_kg = _infos->Option_Tension_kg();
        _last_tension_kg = _current_tension_kg;

        _tension_linear_interpolator = std::shared_ptr<base::LinearInterpolator>{
            new base::LinearInterpolator{
                base::LinearInterpolator_StartVlaue{0},
                base::LinearInterpolator_EndVlaue{_infos->Option_Tension_kg()},
                base::LinearInterpolator_StepLength{0.03},
            },
        };
    }

    void Execute() override;
};
