#pragma once
#include <cstdint>

/*
    probably going to stay conceptual until i feel like implementation
    PACKET HEADER 16 bytes -> 
        [type 1b][version 1b][length 2b][sender 4b][reciever 4b][sequence 4b]     
*/

namespace Packet {
    enum class Type : std::uint8_t {
        Input = 0,               // user actions -> move, shoot, jump 
        ServerStateUpdate = 1,   // given client packets -> update to every client from server
    };

    using PlayerId = std::uint32_t; // 4 billion unique ids

    struct Header {
        Type           type;    // global or one unique client packet update         
        std::uint8_t   version; // protocol version, bump this if you change format
        std::uint16_t  length;  // FULL packet size including header (in bytes)

        PlayerId      sender;   // who sent this packet
        PlayerId      receiver; // target; WORLD_ID == broadcast
        std::uint32_t sequence; // sequencing (packet loss detection)
    };

    // delta
    //struct InputPayload {
    //    float dx;
    //    float dy;
    //};
}