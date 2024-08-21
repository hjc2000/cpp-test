#pragma once

class AutoSleepAutoWakeUp
{
private:
    AutoSleepAutoWakeUp() = default;

public:
    static AutoSleepAutoWakeUp &Instance()
    {
        static AutoSleepAutoWakeUp o;
        return o;
    }

    void Execute();
};
