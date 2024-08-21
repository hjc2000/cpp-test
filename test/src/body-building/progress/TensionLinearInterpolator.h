#pragma once
#include <base/math/LinearInterpolator.h>
#include <memory>

/// @brief 拉力插值器。
class TensionLinearInterpolator
{
private:
    TensionLinearInterpolator() = default;

    std::shared_ptr<base::LinearInterpolator> _linear_interpolator = nullptr;
    int _current_output = 0;

public:
    static TensionLinearInterpolator &Instance()
    {
        static TensionLinearInterpolator o;
        return o;
    }

    void ChangeEndValue(int value);

    int StepForward();
    int CurrentOutput();
};
