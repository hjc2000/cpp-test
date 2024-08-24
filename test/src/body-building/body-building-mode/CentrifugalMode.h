#pragma once
#include <base/IExecutable.h>
#include <base/math/InertialElement.h>
#include <memory>

/// @brief 离心模式
class CentrifugalMode : public base::IExecutable
{
private:
    /// @brief 大于 1 的值。
    /// @note 离心模式下，顺从它离心，拉力会减小。减小拉力是通过将转矩除以本系数。
    /// @return
    double Ratio()
    {
        return 2;
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
