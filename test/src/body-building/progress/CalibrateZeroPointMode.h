#pragma once

/// @brief 零点校准模式
class CalibrateZeroPointMode
{
private:
    CalibrateZeroPointMode() = default;

    bool _is_completed = false;

public:
    static CalibrateZeroPointMode &Instance()
    {
        static CalibrateZeroPointMode o;
        return o;
    }

    void Execute();

    bool IsCompleted() const;
};
