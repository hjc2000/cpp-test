#pragma once

class P_PI_Switch
{
private:
    P_PI_Switch() = default;

public:
    static P_PI_Switch &Instance()
    {
        static P_PI_Switch o;
        return o;
    }

    void Execute();
};
