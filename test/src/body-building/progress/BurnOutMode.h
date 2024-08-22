#pragma once

class BurnOutMode
{
private:
    BurnOutMode() = default;

public:
    static BurnOutMode &Instance()
    {
        static BurnOutMode o;
        return o;
    }

    void Execute();
};
