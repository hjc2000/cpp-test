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

void Servo::RefreshFeedbackPosition()
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
