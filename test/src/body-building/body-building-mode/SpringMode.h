#pragma once

class SpringMode
{
private:
    SpringMode() = default;

public:
    static SpringMode &Instance()
    {
        static SpringMode o;
        return o;
    }

    void Execute();
};
