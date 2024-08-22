#pragma once

/// @brief 摩擦转矩计算器
class FrictionTorqueCalculater
{
private:
    FrictionTorqueCalculater() = default;

    /// @brief 收线时的摩擦转矩
    /// @return
    int WindingFrictionTorque() const;

    /// @brief 放线时的摩擦转矩
    /// @param tension_kg
    /// @return
    int UnwindingFrictionTorque(double tension_kg) const;

public:
    static FrictionTorqueCalculater &Instance()
    {
        static FrictionTorqueCalculater o;
        return o;
    }

    /// @brief 计算摩擦转矩
    /// @param tension_kg 希望输出的拉力大小
    /// @return 摩擦转矩。是个矢量。
    int FrictionTorque(double tension_kg);
};
