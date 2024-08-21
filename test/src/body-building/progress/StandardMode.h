#pragma once

class StandardMode
{
private:
    StandardMode() = default;

public:
    static StandardMode &Instance()
    {
        static StandardMode o;
        return o;
    }

    void Execute();
};
