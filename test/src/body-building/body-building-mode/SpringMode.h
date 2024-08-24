#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <memory>

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

public:
    void Execute();
};
