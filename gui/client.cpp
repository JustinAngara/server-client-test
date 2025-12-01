#include "client.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")

Client::Client(const std::string& serverIp = "127.0.0.1", unsigned short port = 54000)
    : serverIp_(serverIp),
    port_(port),
    isOn_(false),
    out_(INVALID_SOCKET) {
}

Client::~Client() {
    stop();
}

bool Client::start() {
    if (isOn_) {
        std::cout << "client is already on\n";
        return true;
    }

    WSADATA data{};
    WORD version{ MAKEWORD(2, 2) };
    int wsOk{ WSAStartup(version, &data) };
    if (wsOk != 0) {
        std::cout << "cant start winsock " << wsOk << '\n';
        return false;
    }

    std::memset(&server_, 0, sizeof(server_));
    server_.sin_family = AF_INET;
    server_.sin_port = htons(port_);

    if (inet_pton(AF_INET, serverIp_.c_str(), &server_.sin_addr) != 1) {
        std::cout << "inet_pton failed\n";
        WSACleanup();
        return false;
    }

    out_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (out_ == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << '\n';
        WSACleanup();
        return false;
    }

    isOn_ = true;
    return true;
}

void Client::stop() {
    if (out_ != INVALID_SOCKET) {
        closesocket(out_);
        out_ = INVALID_SOCKET;
    }
    if (isOn_) {
        WSACleanup();
        isOn_ = false;
    }
}



bool Client::sendMessage(const std::string& msg) {
    if (!isOn_ || out_ == INVALID_SOCKET) {
        std::cout << "client not started or socket invalid\n";
        return false;
    }

    if (msg.empty()) {
        return true; // nothing to send, but not an error
    }

    int sendOk = sendto(
        out_,
        msg.c_str(),
        static_cast<int>(msg.size()),
        0,
        reinterpret_cast<sockaddr*>(&server_),
        sizeof(server_)
    );

    if (sendOk == SOCKET_ERROR) {
        std::cout << "sendto error " << WSAGetLastError() << '\n';
        return false;
    }

    return true;
}
