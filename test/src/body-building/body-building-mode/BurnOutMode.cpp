#include "BurnOutMode.h"

void BurnOutMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
    }
}
