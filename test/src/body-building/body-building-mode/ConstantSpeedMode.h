#pragma once

class ConstantSpeedMode
{
private:
    ConstantSpeedMode() = default;

public:
    static ConstantSpeedMode &Instance()
    {
        static ConstantSpeedMode o;
        return o;
    }

    void Execute();
};
