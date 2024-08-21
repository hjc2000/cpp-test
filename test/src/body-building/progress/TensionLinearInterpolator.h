#pragma once

/// @brief 拉力插值器。
class TensionLinearInterpolator
{
private:
    TensionLinearInterpolator() = default;

public:
    static TensionLinearInterpolator &Instance()
    {
        static TensionLinearInterpolator o;
        return o;
    }
};
