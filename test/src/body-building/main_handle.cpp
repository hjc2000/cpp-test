#include "main_handle.h"
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>
#include <State.h>

void Refresh()
{
    Servo::Instance().Refresh_FeedbackPosition();
    Option::Instance().Refresh_AdditionalMode();
    Option::Instance().Refresh_BodyBuildingMode();
    Option::Instance().Refresh_Tension_kg();
    State::Instance().Refresh_ReleasedLengthOfLine();
}

void main_handle()
{
    while (true)
    {
        if (true) // 假设已经检查定时时间到了
        {
            // 重置定时器
            // ResetTimer()

            Refresh();
            Cmd::Instance().SendToServo();
        }
    }
}
