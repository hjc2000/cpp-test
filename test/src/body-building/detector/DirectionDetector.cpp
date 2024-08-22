#include "DirectionDetector.h"
#include <State.h>

void DirectionDetector::Execute()
{
    int current_released_length_of_line = State::Instance().ReleasedLengthOfLine();
    if (current_released_length_of_line - _last_released_length_of_line > 20)
    {
        // 当前正在放线
        _current_direction = DirectionDetector_Direction::Unwinding;
        _released_length_of_line_when_direction_change = _last_released_length_of_line;
    }
    else if (current_released_length_of_line - _last_released_length_of_line < -20)
    {
        // 当前正在收线
        _current_direction = DirectionDetector_Direction::Winding;
        _released_length_of_line_when_direction_change = _last_released_length_of_line;
    }

    _last_released_length_of_line = current_released_length_of_line;
}

DirectionDetector_DirectionChange DirectionDetector::DirectionChange() const
{
    if (_last_direction == DirectionDetector_Direction::Winding &&
        _current_direction == DirectionDetector_Direction::Unwinding)
    {
        return DirectionDetector_DirectionChange::FromWindingToUnwinding;
    }
    else if (_last_direction == DirectionDetector_Direction::Unwinding &&
             _current_direction == DirectionDetector_Direction::Winding)
    {
        return DirectionDetector_DirectionChange::FromUnwindingToWinding;
    }
    else
    {
        return DirectionDetector_DirectionChange::None;
    }
}
