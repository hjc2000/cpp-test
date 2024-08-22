#pragma once
#include <base/math/InertialElement.h>
#include <memory>

/// @brief 弹簧模式
class SpringMode
{
private:
    SpringMode() = default;

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

public:
    static SpringMode &Instance()
    {
        static SpringMode o;
        return o;
    }

    void Execute();
};
