#include "DirectionDetector.h"
#include <State.h>

base::DirectionDetecter &DI_DirectionDetecter()
{
    static base::DirectionDetecter detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-20},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

    return detecter;
}
