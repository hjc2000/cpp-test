#include "Servo.h"

void Servo::Disable()
{
}

void Servo::Enable()
{
}

int Servo::Version()
{
    return 20;
}

void Servo::Refresh_FeedbackPosition()
{
    _last_feedback_position = _feedback_position;
    _feedback_position = 0; // 这里先赋值为 0，实际上是要从外界获取信息的
}

int64_t Servo::FeedbackPosition()
{
    return _feedback_position;
}

int64_t Servo::LastFeedbackPosition()
{
    return _last_feedback_position;
}

double Servo::FeedbackSpeed()
{
    return 0.0;
}

bool Servo::CounterClockwiseIsForward()
{
    return true;
}

void Servo::SetSpeed(double value)
{
}

int Servo::TorqueLimit()
{
    return 0;
}

void Servo::SetTorqueLimit(int value)
{
}

int Servo::OverloadForecast()
{
    return 0;
}

int32_t Servo::CommandTorque()
{
    return 0;
}

void Servo::Use_P_Control()
{
}

void Servo::Use_PI_Control()
{
}

void Servo::SetCurrentPositonAsZeroPoint()
{
}
