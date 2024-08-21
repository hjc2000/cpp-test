#include "State.h"
#include <Servo.h>

void State::Refresh_ReleasedLengthOfLine()
{
    _last_released_length_of_line = _released_length_of_line;
    _released_length_of_line = Servo::Instance().FeedbackPosition() * 3.7 * 2 * 3.14 / 12000;
}

double State::ReleasedLengthOfLine()
{
    return _released_length_of_line;
}

double State::LastReleasedLengthOfLine()
{
    return _last_released_length_of_line;
}

bool State::ReleasedLengthOfLineChanged()
{
    return _released_length_of_line != _last_released_length_of_line;
}

bool State::IsTurningForward()
{
    if (Servo::Instance().FeedbackSpeed() > 100)
    {
        _is_turning_forward = true;
    }
    else if (Servo::Instance().FeedbackSpeed() < -100)
    {
        _is_turning_forward = false;
    }

    return _is_turning_forward;
}
