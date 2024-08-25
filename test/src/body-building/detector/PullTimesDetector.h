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
    void Input(double released_length_of_line);

    /// @brief 收绳次数发生变化。接下来可以检查 TurningPoint 属性获取变化瞬间的绳长。
    /// @return
    bool WindingTimesChanged() const
    {
        return _winding_times_changed;
    }

    /// @brief 放绳次数发生变化。接下来可以检查 TurningPoint 属性获取变化瞬间的绳长。
    /// @return
    bool UnwindingTimesChanged() const
    {
        return _unwinding_times_changed;
    }

    /// @brief 转折点
    /// @note 收绳次数变化或放绳次数变化时，可以检查本属性，获取变化瞬间的方向切换转折点。
    /// 转折点就是方向切换瞬间的线长，也是收绳次数或放绳次数发生递增的瞬间的线长。
    /// @return
    double TurningPoint() const
    {
        return _direction_detecter->TurningPoint();
    }

    /// @brief 收绳次数。
    /// @return
    int WindingTimes() const
    {
        return _winding_times;
    }

    /// @brief 放绳次数。
    /// @return
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
