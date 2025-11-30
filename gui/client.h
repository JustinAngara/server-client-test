#pragma once

#include <string>
#include <winsock2.h>

class Client {
public:
    Client(const std::string& serverIp, unsigned short port);
    ~Client();

    bool start();                           // init Winsock + socket
    void stop();                            // cleanup

    bool sendMessage(const std::string& msg);

private:


    std::string serverIp_;
    unsigned short port_;
    bool isOn_;
    SOCKET out_;
    sockaddr_in server_;
};
