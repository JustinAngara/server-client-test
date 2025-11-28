#include "client.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <future>

#pragma comment (lib, "ws2_32.lib")

static std::string readLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

Client::Client(const std::string& serverIp, unsigned short port)
    : serverIp_(serverIp),
    port_(port),
    isOn_(false) {
}

Client::~Client() {
    stop();
}

void Client::start() {
    if (isOn_) {
        std::cout << "client is already on\n";
        return;
    }

    isOn_ = true;
    future_ = std::async(std::launch::async, &Client::run, this);
}

void Client::stop() {
    if (future_.valid()) {
        // optional: future_.wait();
    }
}

int Client::run() {
    std::cout << "Now in client\n";

    WSADATA data{};
    WORD version{ MAKEWORD(2, 2) };
    int wsOk{ WSAStartup(version, &data) };
    if (wsOk != 0) {
        std::cout << "cant start winsock " << wsOk << '\n';
        isOn_ = false;
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port_);

    if (inet_pton(AF_INET, serverIp_.c_str(), &server.sin_addr) != 1) {
        std::cout << "inet_pton failed\n";
        WSACleanup();
        isOn_ = false;
        return 1;
    }

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
    if (out == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << '\n';
        WSACleanup();
        isOn_ = false;
        return 1;
    }

    std::string input{ readLine() };
    while (!input.empty()) {

        int sendOk = sendto(
            out,
            input.c_str(),
            static_cast<int>(input.size() + 1),
            0,
            reinterpret_cast<sockaddr*>(&server),
            sizeof(server)
        );

        if (sendOk == SOCKET_ERROR) {
            std::cout << "error " << WSAGetLastError() << '\n';
            closesocket(out);
            WSACleanup();
            isOn_ = false;
            return 1;
        }

        input = readLine();
    }

    closesocket(out);
    WSACleanup();
    isOn_ = false;
    return 0;
}
