#include "Cmd.h"
#include <math.h>
#include <Servo.h>

int Cmd::Torque() const
{
    return _torque;
}

void Cmd::SetTorque(int value)
{
    _torque = std::abs(value);
}

double Cmd::Speed() const
{
    return _speed;
}

void Cmd::SetSpeed(double value)
{
    _speed = std::abs(value);
}

void Cmd::SendToServo()
{
    Servo::Instance().SetTorqueLimit(Torque());
    Servo::Instance().SetSpeed(Speed());
}
