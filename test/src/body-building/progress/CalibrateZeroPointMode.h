#pragma once

class CalibrateZeroPointMode
{
private:
    CalibrateZeroPointMode() = default;

public:
    static CalibrateZeroPointMode &Instance()
    {
        static CalibrateZeroPointMode o;
        return o;
    }
};
