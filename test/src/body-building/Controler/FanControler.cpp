#include "FanControler.h"
#include <cmath>
#include <Option.h>
#include <Servo.h>

std::chrono::seconds FanControler::TurnOnFanDelay()
{
    return std::chrono::seconds();
}

std::chrono::seconds FanControler::TurnOffFanDelay()
{
    return std::chrono::seconds();
}

int64_t FanControler::TurnOnDelayTick()
{
    // 脚本定时器周期是 2ms，所以乘上 500，每一秒对应 500 个计数。
    return TurnOnFanDelay().count() * 500;
}

int64_t FanControler::TurnOffDelayTick()
{
    // 脚本定时器周期是 2ms，所以乘上 500，每一秒对应 500 个计数。
    return TurnOffFanDelay().count() * 500;
}

void FanControler::Execute()
{
    _hysteresis_element.ChangeThreshold(TurnOnDelayTick(),
                                        TurnOnDelayTick() - TurnOffDelayTick());

    if (Servo::Instance().FeedbackPosition() >= Option::Instance().ZeroPositionProtectionThreshold())
    {
        if (_hysteresis_element.CurrentInput() < TurnOnDelayTick())
        {
            _hysteresis_element.Input(_hysteresis_element.CurrentInput() + 1);
        }
    }
    else
    {
        if (_hysteresis_element.CurrentInput() > TurnOffDelayTick())
        {
            _hysteresis_element.Input(_hysteresis_element.CurrentInput() - 1);
        }
    }

    if (_hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Rise)
    {
        ServoFan::Instance().TurnOn();
    }
    else if (_hysteresis_element.OutputChange() == base::HysteresisElement_OutputChange::Fall)
    {
        ServoFan::Instance().TurnOff();
    }
}
