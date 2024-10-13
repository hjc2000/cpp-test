#include "PcapInitializer.h"

void net::PcapInitializer::Initialize()
{
    std::lock_guard l{_lock};
    if (_initialized)
    {
        return;
    }

    _initialized = true;
    char error_message_buffer[1024]{};
    int result = pcap_init(PCAP_CHAR_ENC_UTF_8, error_message_buffer);
    if (result)
    {
        throw std::runtime_error{std::string{error_message_buffer}};
    }
}
