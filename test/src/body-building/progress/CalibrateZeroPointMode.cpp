#include "CalibrateZeroPointMode.h"
#include <cmath>
#include <Cmd.h>
#include <Option.h>
#include <Servo.h>

void CalibrateZeroPointMode::Execute()
{
    if (_is_completed)
    {
        _progress = 2;
        return;
    }

    _progress = 1;
    if (std::abs(Servo::Instance().FeedbackSpeed()) < 20)
    {
        _zero_speed_holding_tick++;
        if (_zero_speed_holding_tick > 1000)
        {
            _zero_speed_holding_tick = 0;
            Cmd::Instance().SetSpeed(0);
            Cmd::Instance().SetTorque(0);
            Cmd::Instance().SendToServo();
            _is_completed = true;
            _progress = 2;
            Servo::Instance().SetCurrentPositonAsZeroPoint();

            // 触发回调
            if (_on_completed)
            {
                _on_completed();
            }
        }
    }
    else
    {
        _zero_speed_holding_tick = 0;
        Cmd::Instance().SetSpeed(Option::Instance().ReturnToZeroSpeed());
        Cmd::Instance().SetTorque(Option::Instance().ReturnToZeroTorque());
    }
}

bool CalibrateZeroPointMode::IsCompleted() const
{
    return _is_completed;
}

int CalibrateZeroPointMode::Progress()
{
    return _progress;
}

void CalibrateZeroPointMode::Reset()
{
    _is_completed = false;
    _progress = 1;
}
