#pragma once

class State
{
private:
    double _released_length_of_line = 0;
    double _last_released_length_of_line = 0;
    bool _is_turning_forward = false;

public:
    void Refresh_ReleasedLengthOfLine();
    double ReleasedLengthOfLine();
    double LastReleasedLengthOfLine();
    bool ReleasedLengthOfLineChanged();

    /// @brief 伺服在正转
    /// @return 返回 true 表示在正转，返回 false 表示在反转。
    bool IsTurningForward();
};
