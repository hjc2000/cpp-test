#include "FrictionTorqueCalculater.h"
#include <Option.h>

int FrictionTorqueCalculater::WindingFrictionTorque() const
{
    return 4 * Option::Instance().TorqueRatio();
}

int FrictionTorqueCalculater::UnwindingFrictionTorque(double tension_kg) const
{
    return 0;
}

int FrictionTorqueCalculater::FrictionTorque(double tension_kg)
{
    return 0;
}
