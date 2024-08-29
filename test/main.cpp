#include <algorithm>
#include <base/container/IEnumerable.h>
#include <base/container/List.h>
#include <base/container/StdContainerEnumerable.h>
#include <base/Initializer.h>
#include <base/math/ChXFilter.h>
#include <base/math/DirectionDetecter.h>
#include <base/SingletonGetter.h>
#include <base/string/ToHexString.h>
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

class IntSingleTonGetter :
    public base::SingletonGetter<int>
{
protected:
    void Lock() override
    {
        std::cout << "锁定" << std::endl;
    }

    void Unlock() override
    {
        std::cout << "解锁" << std::endl;
    }

    std::unique_ptr<int> Create() override
    {
        return std::unique_ptr<int>{new int{666}};
    }
};

int main(void)
{
    try
    {
        for (int i = 0; i < 5; i++)
        {
            IntSingleTonGetter g{};
            std::cout << (*g)++ << std::endl;
        }

        // std::filesystem::current_path(Predefine_ResourceDir);
        // test_SptsEncodeMux();
        // test_AVPacketPlayer();
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
