#pragma once

/// @brief 向心模式
class CentripetalMode
{
private:
    CentripetalMode() = default;

public:
    static CentripetalMode &Instance()
    {
        static CentripetalMode o;
        return o;
    }

    void Execute();
};
