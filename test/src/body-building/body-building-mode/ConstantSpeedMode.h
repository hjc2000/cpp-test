#pragma once
#include <lua_api.h>

class ConstantSpeedMode
{
private:
    ConstantSpeedMode() = default;

    /// @brief 限制转速时让转矩增长的比例。越大转矩随着速度变大增长越快。
    /// @return
    double TorqueGrowRatio();

    /// @brief 转速限制值。超过后转矩会快速增大。
    /// @return
    double SpeedLimit();

    /// @brief 恒速模式的收线转矩。
    /// @return
    int Torque();

    /// @brief 恒速模式下的收线转速。
    /// @return
    double WindingSpeed();

    /// @brief ChX 滤波器的前向通道增益
    /// @return
    int FilterGain();

public:
    static ConstantSpeedMode &Instance()
    {
        static ConstantSpeedMode o;
        return o;
    }

    void Execute();
};
