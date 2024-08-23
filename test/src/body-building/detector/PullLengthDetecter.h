#pragma once

/// @brief 拉绳长度检测器
class PullLengthDetecter
{
private:
    PullLengthDetecter() = default;

    int _min_length = 0;
    int _max_length = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;

public:
    static PullLengthDetecter &Instance()
    {
        static PullLengthDetecter o;
        return o;
    }

    void Execute();

    /// @brief 本轮拉绳绳子被拉出的长度
    /// @return
    int PullLength()
    {
        int length = _max_length - _min_length;
        if (length < 0)
        {
            length = 0;
        }

        return length;
    }
};
