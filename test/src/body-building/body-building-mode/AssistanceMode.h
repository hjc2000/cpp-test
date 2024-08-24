#pragma once
#include <base/IExecutable.h>
#include <base/math/DirectionDetecter.h>

class AssistanceMode :
    public base::IExecutable
{
private:
    int _unwinding_tick = 0;
    double _tension = 0;
    bool _has_effective_unwinding = false;
    bool _has_effective_winding = false;

    base::DirectionDetecter _direction_detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-20},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

    void OnFromUnwindingToWinding();
    void OnFromWindingToUnwinding();
    double CalSubKg(double base_kg);

public:
    void Execute() override;
};
