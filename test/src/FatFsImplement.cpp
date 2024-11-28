#include <algorithm>
#include <chrono>
#include <cstdint>
#include <diskio.h>
#include <ff.h>

namespace
{
    // 定义一个静态数组作为磁盘存储空间
    uint8_t _buffer[16 * 1024 * 1024]; // 16KB的存储空间

// 每个扇区的大小（单位：字节）
#define SECTOR_SIZE 512

} // namespace

extern "C"
{
    DSTATUS disk_initialize(BYTE pdrv)
    {
        // 初始化磁盘驱动器
        // 这里假设初始化总是成功的
        return 0; // 返回0表示成功
    }

    DSTATUS disk_status(BYTE pdrv)
    {
        // 获取磁盘的状态
        // 假设磁盘总是处于良好状态
        return 0; // 返回0表示正常
    }

    DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
    {
        // 从磁盘读取指定数量的扇区到缓冲区
        std::copy(_buffer + sector * SECTOR_SIZE,
                  _buffer + (sector + count) * SECTOR_SIZE,
                  buff);

        return RES_OK; // 成功
    }

    DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
    {
        std::copy(buff, buff + count * SECTOR_SIZE, _buffer + sector * SECTOR_SIZE);
        return RES_OK; // 成功
    }

    DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
    {
        // 控制磁盘设备
        switch (cmd)
        {
        case CTRL_SYNC: // 刷新缓存到磁盘
            {
                // 对于模拟磁盘，这里不需要做任何事情
                break;
            }
        case GET_SECTOR_COUNT: // 获取磁盘上的总扇区数
            {
                *reinterpret_cast<DWORD *>(buff) = sizeof(_buffer) / SECTOR_SIZE;
                break;
            }
        case GET_SECTOR_SIZE: // 获取每个扇区的大小
            {
                *reinterpret_cast<WORD *>(buff) = SECTOR_SIZE;
                break;
            }
        case GET_BLOCK_SIZE: // 获取擦除块的大小（以扇区为单位）
            {
                // 对于模拟磁盘，我们假设擦除块大小等于一个扇区
                *reinterpret_cast<DWORD *>(buff) = 1;
                break;
            }
        default:
            {
                return RES_PARERR; // 参数错误
            }
        }

        return RES_OK; // 成功
    }

    // 使用 std::chrono 获取当前时间并转换为 FatFs 时间戳
    DWORD get_fattime(void)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        struct tm *now_tm = std::localtime(&now_c);

        // FatFs 时间戳格式：YYYYMMDD HHMMSS
        DWORD fat_time = ((now_tm->tm_year + 1900 - 1980) << 25) |
                         ((now_tm->tm_mon + 1) << 21) |
                         (now_tm->tm_mday << 16) |
                         (now_tm->tm_hour << 11) |
                         (now_tm->tm_min << 5) |
                         (now_tm->tm_sec >> 1);

        return fat_time;
    }
}
