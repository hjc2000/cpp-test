#pragma once
#include <base/IExecutable.h>
#include <base/math/ChXFilter.h>
#include <base/math/LinearInterpolator.h>
#include <Cmd.h>
#include <memory>

class ICentrifugalMode_InfomationGetter
{
public:
    /// @brief 离心比例
    /// @note 大于 1 的值。离心模式下，顺从它离心，拉力会减小。减小拉力是通过将转矩除以本系数。
    /// @return
    virtual double Option_CentrifugalRatio() = 0;

    virtual double Option_Tension_kg() = 0;
    virtual double Option_TorqueRatio() = 0;
    virtual double Option_WindingSpeed_rpm() = 0;

    virtual double Servo_FeedbackSpeed() = 0;
};

/// @brief 离心模式
class CentrifugalMode :
    public base::IExecutable
{
private:
    double _last_tension = 0;
    std::shared_ptr<Cmd> _cmd;
    std::shared_ptr<ICentrifugalMode_InfomationGetter> _infos;
    std::shared_ptr<base::LinearInterpolator> _tension_linear_interpolator;

    std::shared_ptr<base::ChXFilter> _filter{
        new base::ChXFilter{
            base::ChXFilter_KError{10},
            base::ChXFilter_FeedbackDiv{1000},
        },
    };

public:
    CentrifugalMode(std::shared_ptr<Cmd> cmd,
                    std::shared_ptr<ICentrifugalMode_InfomationGetter> infos);

    void Execute();
};
