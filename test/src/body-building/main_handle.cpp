#include "main_handle.h"
#include <AdditionMode.h>
#include <AssistanceMode.h>
#include <BurnOutMode.h>
#include <CalibrateZeroPointMode.h>
#include <CentrifugalMode.h>
#include <CentripetalMode.h>
#include <Cmd.h>
#include <ConstantSpeedMode.h>
#include <DirectionDetector.h>
#include <IntelligentMode.h>
#include <Option.h>
#include <PullTimesDetector.h>
#include <Servo.h>
#include <SleepControler.h>
#include <SpringMode.h>
#include <StallProtectionMode.h>
#include <StandardMode.h>
#include <State.h>

/// @brief 更新外界输入信息和基于它们计算出来的信息。
/// @note 顺序很重要。信息之间有依赖关系。
void Refresh()
{
    Servo::Instance().Refresh_FeedbackPosition();
    Option::Instance().Refresh_AdditionalMode();
    Option::Instance().Refresh_BodyBuildingMode();
    Option::Instance().Refresh_Tension_kg();
    State::Instance().Refresh_ReleasedLengthOfLine();

    DirectionDetector::Instance().Execute();
    PullTimesDetector::Instance().Execute();
}

void Initialize()
{
    Servo::Instance().Use_PI_Control();
    ServoFan::Instance().TurnOff();
}

void SelectOneModeToExecute()
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

/// @brief 模式执行完之后继续对转速、转矩加工，进行一些限制或补偿。
void Limit()
{
}

void RecodeStatus()
{
}

void main_handle()
{
    Initialize();

    CalibrateZeroPointMode::Instance()._on_completed = [&]()
    {
        if (Option::Instance().AutoDisableServoAfterReturningToZero())
        {
            AdditionMode::Instance().SetMode(AdditionMode_ModeEnum::GraduallyDisableServo);
        }
    };

    while (true)
    {
        if (true) // 假设已经检查定时时间到了
        {
            // 重置定时器
            // ResetTimer()

            Refresh();
            SelectOneModeToExecute();
            Limit();
            SleepControler::Instance().Execute();
            RecodeStatus();
            Cmd::Instance().SendToServo();
        }
    }
}
