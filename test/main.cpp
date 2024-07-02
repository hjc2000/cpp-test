#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <algorithm>
#include <base/math/Fraction.h>
#include <base/string/ToHexString.h>
#include <ffmpeg-wrapper/mux/SptsEncodeMux.h>
#include <filesystem>
#include <iostream>
#include <sdl2-wrapper/AVPacketPlayer.h>
#include <sstream>
#include <stdexcept>
#include <test_tsduck.h>

extern "C"
{
#include <c-bsp-interface/modbus/ModbusBitConverter.h>
}

using namespace std;

int main(void)
{
	try
	{
		// std::filesystem::current_path(Predefine_ResourceDir);
		// test_SptsEncodeMux();
		// test_AVPacketPlayer();
		// test_tsduck();

		uint8_t buffer[8] = {0};
		ModbusBitConverter_GetBytesFromUInt32(ModbusBitConverterUnit_Record,
											  0x12345678, buffer, 0);

		for (int i = 0; i < static_cast<int>(sizeof(buffer)); i++)
		{
			cout << base::ToHexString(buffer[i]) << ", ";
		}

		cout << endl;
		return 0;
	}
	catch (std::runtime_error &e)
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
