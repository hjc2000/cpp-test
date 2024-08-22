#pragma once

/// @brief 向心模式
class CentrifugalMode
{
private:
    CentrifugalMode() = default;

public:
    static CentrifugalMode &Instance()
    {
        static CentrifugalMode o;
        return o;
    }

    void Execute();
};
