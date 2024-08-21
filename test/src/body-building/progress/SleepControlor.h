#pragma once
#include <base/math/InertialElement.h>

class SleepControlor
{
private:
    SleepControlor() = default;

    base::InertialElement _speed_filter{0.025, 0.002};
    int64_t _auto_sleep_delay_tick = 0;

public:
    static SleepControlor &Instance()
    {
        static SleepControlor o;
        return o;
    }

    void Execute();
};
