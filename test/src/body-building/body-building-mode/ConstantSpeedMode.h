#pragma once
#include <lua_api.h>

class ConstantSpeedMode
{
private:
    ConstantSpeedMode() = default;

    /// @brief 限制转速时让转矩增长的比例。越大转矩随着速度变大增长越快。
    /// @return
    double TorqueGrowRatio()
    {
        return SRV_PARA(1, 39) / 1000;
    }

    /// @brief 转速限制值。超过后转矩会快速增大。
    /// @return
    double SpeedLimit()
    {
        return SRV_PARA(1, 21) / 100;
    }

    /// @brief 恒速模式的收线转矩。
    /// @return
    int Torque()
    {
        return SRV_PARA(2, 18);
    }

    /// @brief 恒速模式下的收线转速。
    /// @return
    double WindingSpeed()
    {
        return SRV_PARA(1, 10) / 100;
    }

public:
    static ConstantSpeedMode &Instance()
    {
        static ConstantSpeedMode o;
        return o;
    }

    void Execute();
};
