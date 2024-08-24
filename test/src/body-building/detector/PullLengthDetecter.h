#pragma once
#include <base/math/DirectionDetecter.h>

/// @brief 拉绳长度检测器
class PullLengthDetecter
{
private:
    PullLengthDetecter() = default;

    int _starting_point = 0;
    int _pull_length = 0;
    int _last_pull_length = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;

    base::DirectionDetecter _direction_detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-20},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

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
        return _pull_length;
    }

    /// @brief 上一轮绳子被拉出的长度
    /// @return
    int LastPullLength()
    {
        return _last_pull_length;
    }
};
