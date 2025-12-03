#pragma once
#include <cstdint>


namespace Packet {
    enum class Type : std::uint8_t {
        Input = 0,               // user actions -> move, shoot, jump 
        ServerStateUpdate = 1,   // given client packets -> update to every client from server
    };

    using PlayerId = std::uint32_t; 

    struct Header {
        Type     type;        // what kind of packet this is
        std::uint8_t   version;     // protocol version, bump this if you change format
        std::uint16_t  length;      // FULL packet size including header (in bytes)

        PlayerId       sender;      // who sent this packet
        PlayerId       receiver;    // target; WORLD_ID == broadcast
        std::uint32_t  sequence;    // sequencing (anti replay, ordering, drop detection)
    };
}