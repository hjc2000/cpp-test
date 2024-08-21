#include "main_handle.h"
#include <AdditionMode.h>
#include <CalibrateZeroPointMode.h>
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>
#include <SleepControler.h>
#include <State.h>

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

    // 健身模式
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
