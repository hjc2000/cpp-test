#pragma once
#include <iostream>

/// @brief 最终会发送给伺服的指令。
class Cmd
{
private:
    int _torque = 0;
    double _speed = 0;

public:
    /// @brief 转矩。本属性最终会用来设置伺服的转矩限制值。
    /// @return
    int Torque() const;

    /// @brief 设置转矩。本属性最终会用来设置伺服的转矩限制值。
    /// @param value 转矩限制值。只有大小，没有方向和正负。输入的数会被取绝对值。
    void SetTorque(int value);

    /// @brief 转速。本属性最终会用来设置伺服的转速。
    /// @return
    double Speed() const;

    /// @brief 设置转速。
    /// @param value 速率。只有大小，没有方向和正负。输入的数会被取绝对值。
    void SetSpeed(double value);

    /// @brief 将命令送给伺服。
    void SendToServo();
};

std::ostream &operator<<(std::ostream &os, Cmd const &cmd);
