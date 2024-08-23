#pragma once

class BurnOutMode
{
private:
    BurnOutMode() = default;

    int _burn_out_tick = 0;

public:
    static BurnOutMode &Instance()
    {
        static BurnOutMode o;
        return o;
    }

    void Execute();
};
