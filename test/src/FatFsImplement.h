#pragma once
#include <diskio.h>
#include <ff.h>

extern "C"
{
    /// @brief 初始化驱动器。
    /// @param pdrv 驱动器号
    /// @return 返回 0 表示成功。
    DSTATUS disk_initialize(BYTE pdrv);

    /// @brief 获取驱动器的状态，指示驱动器是否准备好。
    /// @param pdrv 驱动器号。
    /// @return 返回 0 表示驱动器准备好。
    DSTATUS disk_status(BYTE pdrv);

    /// @brief 读驱动器。
    /// @param pdrv 驱动器号。
    /// @param buff 读取的数据放到此缓冲区。
    /// @param sector 起始扇区号。
    /// @param count 要读取的扇区数量。
    /// @return
    DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count);

    /// @brief 写驱动器。
    /// @param pdrv 驱动器号。
    /// @param buff 要被写入到驱动器的数据缓冲区。
    /// @param sector 起始扇区号。
    /// @param count 要写入的扇区数量。
    /// @return
    DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count);

    /// @brief 驱动器控制。
    /// @param pdrv 驱动器号。
    /// @param cmd 命令。具体有哪些命令见下方的宏定义。
    /// @param buff 命令参数或者命令输出结果。
    /// @return
    DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff);
}
