#include "main_handle.h"
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
        Refresh();
    }
}
