#include "main_handle.h"
#include <AdditionMode.h>
#include <CalibrateZeroPointMode.h>
#include <Cmd.h>
#include <ModeSelector.h>
#include <Option.h>
#include <PullLengthDetecter.h>
#include <PullTimesDetector.h>
#include <Servo.h>
#include <SleepControler.h>
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
}

void Initialize()
{
    Option::Instance().Clear_AdditionalMode();
    Servo::Instance().Use_PI_Control();
    ServoFan::Instance().TurnOff();
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

            PullTimesDetector::Instance().Execute();
            PullLengthDetecter::Instance().Execute();

            ModeSelector::Instance().Execute();
            SleepControler::Instance().Execute();
            RecodeStatus();
            Cmd::Instance().SendToServo();
        }
    }
}
