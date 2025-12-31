#pragma once

#include "NetPacket.h"
#include <string>
#include <winsock2.h>

class Client {
public:
    Client(const std::string& serverIp = "127.0.0.1", unsigned short port = 54000);
    ~Client();
    bool start();                           // init Winsock + socket
    void stop();                            // cleanup

    bool sendMessage(const std::string& msg);
    bool sendPacket(NetPacket::Header header, NetPacket::Payload);


private:


    std::string serverIp_;
    unsigned short port_;
    bool isOn_;
    SOCKET out_;
    sockaddr_in server_;
};
