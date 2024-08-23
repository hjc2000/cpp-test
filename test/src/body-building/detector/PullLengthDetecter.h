#pragma once

/// @brief 拉绳长度检测器
class PullLengthDetecter
{
private:
    PullLengthDetecter() = default;

public:
    static PullLengthDetecter &Instance()
    {
        static PullLengthDetecter o;
        return o;
    }

    void Execute();
};
