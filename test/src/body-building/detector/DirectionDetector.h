#pragma once
#include <base/math/DirectionDetecter.h>

/// @brief 方向检测器
class DirectionDetector
{
private:
    DirectionDetector() = default;

    base::DirectionDetecter _detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-20},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

public:
    static DirectionDetector &Instance()
    {
        static DirectionDetector o;
        return o;
    }

    void Execute();

    int64_t TurningPoint() const
    {
        return _detecter.TurningPoint();
    }

    base::DirectionDetecter_DirectionChange DirectionChange() const
    {
        return _detecter.DirectionChange();
    }
};
