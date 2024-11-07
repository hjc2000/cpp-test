#include <algorithm>
#include <base/container/List.h>
#include <base/di/SingletonGetter.h>
#include <base/math/ChXFilter.h>
#include <base/math/DirectionDetecter.h>
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
#include <windows.h>

/// @brief 以太网帧
/// @note 字段的发送顺序：写在越上面的字段越先发送。
/// @note 每个数组字段的发送顺序：从第 0 个字节开始发送。每个字节都从最高位开始发送。
class EthernetFrame
{
private:
    /// @brief 前导码。
    uint8_t _preamble[7] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

    /// @brief 帧起始符。
    uint8_t _frame_start_character[1] = {0xAB};

    /// @brief 目的 MAC 地址。
    /// @note 大端序，书写 MAC 字符串时，书写在左侧的字节处于数组的低索引处。
    uint8_t _destination_mac[6] = {};

    /// @brief 源 MAC 地址。
    /// @note 大端序，书写 MAC 字符串时，书写在左侧的字节处于数组的低索引处。
    uint8_t _source_mac[6] = {};

    /// @brief 802.1Q标签
    uint8_t _802_1q_tag[4] = {};

    /// @brief 为 true 则表示 _802_1q_tag 此时是有效值。
    /// @note 因为 802.1Q标签 是可选的，所以需要本字段来指示是否有效。
    bool _802_1q_tag_is_avaliable = false;

    /// @brief 类型或长度。
    /// @note 是一个大端序的 16 位整型。
    ///
    /// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
    /// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
    /// 例如下面这几个值都大于 1500：
    /// 	@li 0x0800：表示IPv4数据包
    /// 	@li 0x0806：表示ARP请求
    /// 	@li 0x86DD：表示IPv6数据包
    uint8_t _type_or_length[2] = {};

    /// @brief 载荷数据。
    /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
    uint8_t _payload[1500] = {};

    /// @brief _payload 中要被发送出去的字节数，包括用来凑够 46 字节的填充字节。
    /// 所以取值范围是：[46, 1500].
    /// @note 此字段不是以太网的一部分。
    int32_t _payload_length = 1500;

    /// @brief 冗余校验序列。
    uint8_t _frame_check_sequence[4] = {};

public:
};

int main(void)
{
    try
    {
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
