#include <algorithm>
#include <base/container/List.h>
#include <base/di/SingletonGetter.h>
#include <base/string/ToHexString.h>
#include <filesystem>
#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <sdl2-wrapper/AVPacketPlayer.h>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <windows.h>

void LogBuffer();

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

int main()
{
	int argc = 1;

	char *argv[] = {
		const_cast<char *>("Hello World"),
		nullptr,
	};

	QApplication app{argc, argv};
	QWidget window{};
	window.resize(1920, 1080);
	window.setWindowTitle("Hello World");
	window.showMaximized();
	return app.exec();
}

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
