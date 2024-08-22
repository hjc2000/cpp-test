#pragma once

enum class DirectionDetector_DirectionChange
{
    /// @brief 没有变化
    None,

    /// @brief 从收线到放线
    FromWindingToUnwinding,

    /// @brief 从放线到收线
    FromUnwindingToWinding,
};

enum class DirectionDetector_Direction
{
    /// @brief 收线
    Winding,

    /// @brief 放线
    Unwinding,
};

/// @brief 方向检测器
class DirectionDetector
{
private:
    DirectionDetector() = default;

    DirectionDetector_Direction _current_direction = DirectionDetector_Direction::Winding;
    DirectionDetector_Direction _last_direction = DirectionDetector_Direction::Winding;
    int _last_released_length_of_line = 0;
    int _released_length_of_line_when_direction_change = 0;

public:
    static DirectionDetector &Instance()
    {
        static DirectionDetector o;
        return o;
    }

    void Execute();

    DirectionDetector_Direction CurrentDirection() const
    {
        return _current_direction;
    }

    DirectionDetector_Direction LastDirection() const
    {
        return _last_direction;
    }

    DirectionDetector_DirectionChange DirectionChange() const;

    /// @brief 发生方向切换时的放线长度。
    /// @return
    int ReleasedLengthOfLineWhenDirectionChanged() const
    {
        return _released_length_of_line_when_direction_change;
    }
};
