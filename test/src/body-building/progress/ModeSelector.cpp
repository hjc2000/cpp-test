#include "ModeSelector.h"
#include <AdditionMode.h>
#include <AssistanceMode.h>
#include <BurnOutMode.h>
#include <CalibrateZeroPointMode.h>
#include <CentrifugalMode.h>
#include <CentripetalMode.h>
#include <Cmd.h>
#include <ConstantSpeedMode.h>
#include <IntelligentMode.h>
#include <Option.h>
#include <SpringMode.h>
#include <StallProtectionMode.h>
#include <StandardMode.h>

void ModeSelector::HandleAfterBodyBuildingMode()
{
}

void ModeSelector::SelectOneBodyBuildingModeToExecute()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::Standard:
        {
            StandardMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::IntelligentMode:
        {
            IntelligentMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::CentripetalMode:
        {
            CentripetalMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::CentrifugalMode:
        {
            CentrifugalMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::SpringMode:
        {
            SpringMode::Instance().Execute();
            break;
        }
    default:
    case Option_BodyBuildingMode::Standby:
        {
            Cmd::Instance().SetSpeed(0);
            Cmd::Instance().SetTorque(0);
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            ConstantSpeedMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            ConstantSpeedMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            ConstantSpeedMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            ConstantSpeedMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            ConstantSpeedMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::BurnOutMode:
        {
            BurnOutMode::Instance().Execute();
            break;
        }
    case Option_BodyBuildingMode::AssistanceMode:
        {
            AssistanceMode::Instance().Execute();
            break;
        }
    }
}

void ModeSelector::SelectOneModeToExecute()
{
    if (!CalibrateZeroPointMode::Instance().IsCompleted())
    {
        CalibrateZeroPointMode::Instance().Execute();
        return;
    }

    if (Option::Instance().AdditionalModeCodeChanged())
    {
        AdditionMode::Instance().SetMode(static_cast<AdditionMode_ModeEnum>(Option::Instance().AdditionalMode()));
    }

    if (static_cast<int>(AdditionMode::Instance().Mode()) > 0)
    {
        AdditionMode::Instance().Execute();
        return;
    }

    // 失速保护模式
    if (StallProtectionMode::Instance().StallFlag())
    {
        StallProtectionMode::Instance().Execute();
        return;
    }

    // 健身模式
    SelectOneBodyBuildingModeToExecute();
    HandleAfterBodyBuildingMode();
}

void ModeSelector::Execute()
{
    SelectOneModeToExecute();
}
