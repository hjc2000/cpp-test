#pragma once
#include <base/math/DirectionDetecter.h>
#include <base/math/SlidingHysteresisiElement.h>
#include <memory>

class PullTimesDetector
{
private:
    base::SlidingHysteresisiElement _hys{
        base::HysteresisElement_RisingThreshold{100},
        base::HysteresisElement_FallenThreshold{20},
    };

    std::shared_ptr<base::DirectionDetecter> _direction_detecter{
        new base::DirectionDetecter{
            base::DirectionDetecter_RisingThreshold{20},
            base::DirectionDetecter_FallenThreshold{-20},
            base::DirectionDetecter_Direction::Falling,
            0,
        },
    };

    bool _has_effective_winding = false;
    bool _has_effective_unwinding = false;
    int _winding_times = 0;
    int _unwinding_times = 0;
    bool _winding_times_changed = false;
    bool _unwinding_times_changed = false;

public:
    void Input(int released_length_of_line);

    bool WindingTimesChanged() const
    {
        return _winding_times_changed;
    }

    bool UnwindingTimesChanged() const
    {
        return _unwinding_times_changed;
    }

    int WindingTimes() const
    {
        return _winding_times;
    }

    int UnwindingTimes() const
    {
        return _unwinding_times;
    }

    /// @brief 重置拉绳次数检测器。会重置出绳次数和收绳次数。
    void Reset()
    {
        _winding_times = 0;
        _unwinding_times = 0;
    }
};
