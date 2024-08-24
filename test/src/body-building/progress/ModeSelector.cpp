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

void ModeSelector::CreateBodyBuildingModeExecutable()
{
    switch (Option::Instance().BodyBuildingMode())
    {
    case Option_BodyBuildingMode::Standard:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new StandardMode{}};
            break;
        }
    case Option_BodyBuildingMode::IntelligentMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new IntelligentMode{}};
            break;
        }
    case Option_BodyBuildingMode::CentripetalMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new CentripetalMode{}};
            break;
        }
    case Option_BodyBuildingMode::CentrifugalMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new CentrifugalMode{}};
            break;
        }
    case Option_BodyBuildingMode::SpringMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new SpringMode{}};
            break;
        }
    default:
    case Option_BodyBuildingMode::Standby:
        {
            _body_building_executable = nullptr;
            Cmd::Instance().SetSpeed(0);
            Cmd::Instance().SetTorque(0);
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new ConstantSpeedMode{}};
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new ConstantSpeedMode{}};
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new ConstantSpeedMode{}};
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new ConstantSpeedMode{}};
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new ConstantSpeedMode{}};
            break;
        }
    case Option_BodyBuildingMode::BurnOutMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new BurnOutMode{}};
            break;
        }
    case Option_BodyBuildingMode::AssistanceMode:
        {
            _body_building_executable = std::shared_ptr<base::IExecutable>{new AssistanceMode{}};
            break;
        }
    }
}

void ModeSelector::Execute()
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
    if (Option::Instance().BodyBuildingModeChanged())
    {
        CreateBodyBuildingModeExecutable();
    }

    if (_body_building_executable)
    {
        _body_building_executable->Execute();
        HandleAfterBodyBuildingMode();
    }
}
