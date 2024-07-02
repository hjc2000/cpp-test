#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <algorithm>
#include <base/math/Fraction.h>
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

std::string ToHexString(uint8_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << static_cast<int>(number);
	return string_stream.str();
}

std::string ToHexString(int64_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << number;
	return string_stream.str();
}

std::string ToHexString(uint64_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << number;
	return string_stream.str();
}

int main(void)
{
	try
	{
		// std::filesystem::current_path(Predefine_ResourceDir);
		// test_SptsEncodeMux();
		// test_AVPacketPlayer();
		// test_tsduck();

		uint8_t buffer[8] = {0};
		ModbusBitConverter_GetBytesFromUInt32(ModbusBitConverterUnit_Whole,
											  0x12345678, buffer, 0);

		for (int i = 0; i < static_cast<int>(sizeof(buffer)); i++)
		{
			cout << ToHexString(buffer[i]) << ", ";
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
