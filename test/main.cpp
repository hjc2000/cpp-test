#include <algorithm>
#include <base/container/IEnumerable.h>
#include <base/container/List.h>
#include <base/container/StdContainerEnumerable.h>
#include <base/Initializer.h>
#include <base/math/Fraction.h>
#include <base/math/InertialElement.h>
#include <base/math/LinearInterpolator.h>
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

using namespace std;

// class Base
// {
// public:
//     virtual ~Base() = default;
// };

// class Derive :
//     public Base
// {
// public:
//     std::shared_ptr<int> sp{
//         new int{0},
//         [](int *p)
//         {
//             delete p;
//             std::cout << "666" << endl;
//         },
//     };
// };

int main(void)

{
    try
    {
        // Base *p = new Derive{};
        // delete p;

        base::InertialElement element{0.025, 0.001};
        for (int i = 0; i < 500; i++)
        {
            std::cout << element.Input(15) << std::endl;
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
