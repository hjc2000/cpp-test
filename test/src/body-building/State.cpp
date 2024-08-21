#include "State.h"

void State::Refresh_ReleasedLengthOfLine()
{
    _last_released_length_of_line = _released_length_of_line;
    // _released_length_of_line=
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
