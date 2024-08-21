#pragma once

class FanControler
{
private:
    FanControler() = default;

public:
    static FanControler &Instance()
    {
        static FanControler o;
        return o;
    }
};
