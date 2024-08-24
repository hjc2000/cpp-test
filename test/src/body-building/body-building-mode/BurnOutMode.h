#pragma once
#include <base/IExecutable.h>
#include <base/math/DirectionDetecter.h>

class BurnOutMode :
    public base::IExecutable
{
private:
    int _unwinding_tick = 0;
    double _t2 = 0;
    double _t3 = 0;
    bool _changing = false;
    double _tension = 0;
    int _last_pull_length = 0;
    double _power = 0;
    bool _has_effective_unwinding = false;

    base::DirectionDetecter _direction_detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-20},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

    void OnFromUnwindingToWinding();

public:
    void Execute();
};
