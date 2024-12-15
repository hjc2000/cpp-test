#include <algorithm>
#include <base/container/List.h>
#include <base/di/SingletonGetter.h>
#include <base/math/ChXFilter.h>
#include <base/math/DirectionDetecter.h>
#include <base/string/ToHexString.h>
#include <ff.h>
#include <ffmpeg-wrapper/mux/SptsEncodeMux.h>
#include <filesystem>
#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <sdl2-wrapper/AVPacketPlayer.h>
#include <sstream>
#include <stdexcept>
#include <test_tsduck.h>
#include <time.h>
#include <windows.h>

void LogBuffer();

inline void TestFatFs()
{
	FATFS fatfs{};
	BYTE work[FF_MAX_SS]; // 工作缓冲区
	FRESULT res{};

	// 初始化FatFs模块
	res = f_mount(&fatfs, "", 0); // 卸载任何已挂载的卷
	if (res != FR_OK)
	{
		// 处理错误
		std::cerr << "f_mount error: " << res << std::endl;
	}

	// 创建格式化参数结构体
	MKFS_PARM mkfs_parm{};
	mkfs_parm.fmt = FM_FAT; // 设置文件系统类型为FAT，并创建一个简单的FAT12/FAT16分区
	mkfs_parm.n_fat = 1;    // 设置FAT表的数量为1
	mkfs_parm.align = 1;    // 数据区域对齐为1扇区
	mkfs_parm.n_root = 0;   // 根目录条目数为0（自动选择）
	mkfs_parm.au_size = 0;  // 分配单元大小为自动选择

	// 格式化磁盘
	res = f_mkfs("", &mkfs_parm, work, sizeof(work));
	if (res != FR_OK)
	{
		// 处理错误
		std::cerr << "f_mkfs error: " << res << std::endl;
	}

	LogBuffer();

	// 重新挂载文件系统
	res = f_mount(&fatfs, "", 1); // 挂载文件系统
	if (res != FR_OK)
	{
		// 处理错误
		std::cerr << "f_mount error: " << res << std::endl;
	}

	// 打印当前时间戳
	DWORD fat_time = get_fattime();
	std::cout << "Current FAT time: " << fat_time << std::endl;
	std::cout << "Disk formatted successfully." << std::endl;

	FIL file{};
	char const *filename = "example.txt";
	char const *str = "Hello, FATFS!";

	// 打开或创建文件
	res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
	if (res == FR_OK)
	{
		// 写入字符串到文件
		UINT bytesWritten;
		res = f_write(&file, str, strlen(str), &bytesWritten);
		if (res != FR_OK || bytesWritten != strlen(str))
		{
			printf("写入文件失败: %d\n", res);
		}
		else
		{
			printf("成功写入 %u 字节到文件。\n", bytesWritten);
		}

		// 关闭文件
		f_close(&file);
	}
	else
	{
		printf("打开文件失败: %d\n", res);
	}

	// 重新打开文件以读取
	res = f_open(&file, filename, FA_READ);
	if (res == FR_OK)
	{
		char buffer[128] = {0}; // 假设文件内容不会超过127个字符
		UINT bytesRead;

		// 从文件读取内容
		res = f_read(&file, buffer, sizeof(buffer) - 1, &bytesRead);
		if (res != FR_OK)
		{
			printf("读取文件失败: %d\n", res);
		}
		else
		{
			printf("成功读取 %u 字节: %s\n", bytesRead, buffer);
		}

		// 关闭文件
		f_close(&file);
	}
	else
	{
		printf("打开文件失败: %d\n", res);
	}

	// 卸载文件系统
	f_mount(NULL, "", 0);
}

int main(void)
{
	try
	{
		TestFatFs();

		// MessageBox(NULL, "Hello world!", "标题", MB_OK);
		// return 0;

		std::filesystem::current_path(Predefine_ResourceDir);
		video::test_AVPacketPlayer();

		// test_SptsEncodeMux();
		// test_tsduck();
		return 0;
	}
	catch (std::runtime_error const &e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
}

// int main()
//{
//	int argc = 1;
//	char *argv[] = {(char*)"appname", nullptr};
//	QCoreApplication app(argc, argv);
//
//	qDebug() << "Hello, Qt console application!";
//
//	return app.exec();
// }

// #include<iostream>
// #include<test_boost_asio.h>
// #include<thread>
//
// int main()
//{
//	try
//	{
//		std::thread([&]()
//		{
//			try
//			{
//				receive_udp_message();
//			}
//			catch (std::exception &e)
//			{
//				std::cerr << "Exception: " << e.what() << "\n";
//			}
//		}).detach();
//
//		std::thread([&]()
//		{
//			try
//			{
//				send_udp_message();
//			}
//			catch (std::exception &e)
//			{
//				std::cerr << "Exception: " << e.what() << "\n";
//			}
//		}).detach();
//
//		std::cin.get();
//	}
//	catch (std::exception &e)
//	{
//		std::cerr << "Exception: " << e.what() << "\n";
//	}
//
//	return 0;
// }
