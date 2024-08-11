#pragma once
#include <cstdint>

namespace video
{
    class IRefTimer
    {
    public:
        virtual ~IRefTimer()
        {
        }

    public:
        /// @brief 获取当前的音频时间。单位毫秒。
        /// @return
        virtual int64_t RefTime() = 0;
    };
} // namespace video