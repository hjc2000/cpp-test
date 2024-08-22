#include "main_handle.h"
#include <AdditionMode.h>
#include <CalibrateZeroPointMode.h>
#include <Cmd.h>
#include <DirectionDetector.h>
#include <IntelligentMode.h>
#include <Option.h>
#include <PullTimesDetector.h>
#include <Servo.h>
#include <SleepControler.h>
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
            break;
        }
    case Option_BodyBuildingMode::CentrifugalMode:
        {
            break;
        }
    case Option_BodyBuildingMode::SpringMode:
        {
            break;
        }
    default:
    case Option_BodyBuildingMode::Standby:
        {
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode1:
        {
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode2:
        {
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode3:
        {
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode4:
        {
            break;
        }
    case Option_BodyBuildingMode::ConstantSpeedMode5:
        {
            break;
        }
    case Option_BodyBuildingMode::BurnOutMode:
        {
            break;
        }
    case Option_BodyBuildingMode::AssistanceMode:
        {
            break;
        }
    }
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
            SleepControler::Instance().Execute();
            RecodeStatus();
            Cmd::Instance().SendToServo();
        }
    }
}
