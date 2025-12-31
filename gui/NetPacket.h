#pragma once
#include <cstdint>

namespace NetPacket {

    enum class Type : std::uint8_t {
        Input = 0,
        ServerStateUpdate = 1,
    };

    using PlayerId = std::uint32_t;

    struct Header {
        Type           type;
        std::uint8_t   version;
        std::uint16_t  length;
        PlayerId       sender;
        PlayerId       receiver;
        std::uint32_t  sequence;
    };

    struct Payload {
        // this will include the char byte array itself
        const char* data; 
        std::uint32_t size;
    };
}