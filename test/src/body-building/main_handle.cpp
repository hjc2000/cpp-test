#include "main_handle.h"
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
}

void RecodeStatus()
{
}

void main_handle()
{
    Initialize();
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
