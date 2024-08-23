#pragma once

class BurnOutMode
{
private:
    BurnOutMode() = default;

    int _burn_out_tick = 0;
    double _t2 = 0;
    double _t3 = 0;
    bool _changing = false;
    double _tension = 0;
    int _last_pull_length = 0;
    double _burn_out_power = 0;

    void OnFromUnwindingToWinding();

public:
    static BurnOutMode &Instance()
    {
        static BurnOutMode o;
        return o;
    }

    void Execute();
};
