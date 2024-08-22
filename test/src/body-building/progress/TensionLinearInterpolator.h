#pragma once
#include <base/math/LinearInterpolator.h>
#include <memory>

/// @brief 拉力插值器。
class TensionLinearInterpolator
{
private:
    TensionLinearInterpolator() = default;

    std::shared_ptr<base::LinearInterpolator> _linear_interpolator = nullptr;
    double _current_output = 0;

public:
    static TensionLinearInterpolator &Instance()
    {
        static TensionLinearInterpolator o;
        return o;
    }

    /// @brief 更改拉力插值器的结束值。
    /// @param value
    void ChangeEndValue(double value);

    /// @brief 向前迈进一步并返回迈进后的值。
    /// @return
    double StepForward();

    /// @brief 获取当前输出值。
    /// @return
    double CurrentOutput();
};
