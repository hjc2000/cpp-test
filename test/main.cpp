#include "Poco/Delegate.h"
#include "Poco/Net/Net.h"
#include <algorithm>
#include <base/container/List.h>
#include <base/di/SingletonGetter.h>
#include <base/math/ChXFilter.h>
#include <base/math/DirectionDetecter.h>
#include <base/string/ToHexString.h>
#include <ffmpeg-wrapper/mux/SptsEncodeMux.h>
#include <filesystem>
#include <iostream>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Net/NTPClient.h>
#include <Poco/Timespan.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <sdl2-wrapper/AVPacketPlayer.h>
#include <sstream>
#include <stdexcept>
#include <test_tsduck.h>
#include <time.h>
#include <windows.h>

void LogBuffer();

class MyEventHandler
{
private:
	Poco::Timestamp T1 = Poco::Timestamp(); // Originate Time

public:
	// 定义事件处理器方法
	void onNTPResponse(void const *sender, Poco::Net::NTPEventArgs &args)
	{
		Poco::Timestamp T2 = args.packet().receiveTime();  // Receive Time
		Poco::Timestamp T3 = args.packet().transmitTime(); // Transmit Time
		Poco::Timestamp T4 = Poco::Timestamp();            // Current client time when receiving the response
		Poco::Timespan delay = ((T4 - T1) - (T3 - T2)) / 2;
		Poco::Timespan offset = ((T2 - T1) + (T3 - T4)) / 2;
		Poco::Timestamp accurateTime = T4 + offset;

		// 定义格式字符串
		std::string format = "%Y-%m-%d %H:%M:%S";

		// 使用 Poco::DateTimeFormatter 格式化时间
		std::string formattedTime = Poco::DateTimeFormatter::format(accurateTime, format);

		// 输出格式化后的时间
		std::cout << "Formatted Time: " << formattedTime << std::endl;
	}
};

int main()
{
	Poco::Net::NTPClient client{Poco::Net::SocketAddress::Family::IPv4};
	MyEventHandler eventHandler;
	client.response += Poco::delegate(&eventHandler, &MyEventHandler::onNTPResponse);
	// int result = client.request("ntp.ntsc.ac.cn");
	int result = client.request("time.windows.com");
}

// int main()
// {
// 	try
// 	{
// 		// MessageBox(NULL, "Hello world!", "标题", MB_OK);
// 		// return 0;

// 		std::filesystem::current_path(Predefine_ResourceDir);
// 		video::test_AVPacketPlayer();

// 		// test_SptsEncodeMux();
// 		// test_tsduck();
// 		return 0;
// 	}
// 	catch (std::runtime_error const &e)
// 	{
// 		std::cout << e.what() << std::endl;
// 		throw;
// 	}
// }

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
