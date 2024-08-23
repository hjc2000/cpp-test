#pragma once
#include <base/math/HysteresisElement.h>

class PullTimesDetector
{
private:
    PullTimesDetector() = default;

    base::HysteresisElement _hysteresis_element{
        base::HysteresisElement_RisingThreshold{100},
        base::HysteresisElement_FallenThreshold{20},
    };

    int _winding_times = 0;
    int _unwinding_times = 0;

public:
    static PullTimesDetector &Instance()
    {
        static PullTimesDetector o;
        return o;
    }

    void Execute();

    bool WindingTimesChanged() const;
    bool UnwindingTimesChanged() const;

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
