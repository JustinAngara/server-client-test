#include "server.h"
#include "gui.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <future>

#pragma comment (lib, "ws2_32.lib")

Server::Server(OutputFn outputFn)
    : isOn(false),
    outputFn_(std::move(outputFn)) {
}

Server::~Server() {
    stop();
}
void Server::start() {
    if (isOn) {
        std::cout << "server is already on\n";
        return;
    }

    isOn = true;
    future = std::async(std::launch::async, &Server::run, this);
}

void Server::stop() {
    if (!isOn) {
        return;
    }

    isOn = false;
    // optional: if (future.valid()) future.wait();
}

int Server::run() {
    std::cout << "Now in server \n";

    const int buff_size{ 1024 };

    WSADATA data{};
    WORD version{ MAKEWORD(2, 2) };

    int wsOk{ WSAStartup(version, &data) };
    if (wsOk != 0) {
        std::cout << "cant start winsock " << wsOk << '\n';
        return 1;
    }

    SOCKET in{ socket(AF_INET, SOCK_DGRAM, 0) };
    if (in == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << '\n';
        WSACleanup();
        return 1;
    }

    sockaddr_in serverHint{};
    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(54000);

    if (bind(in, reinterpret_cast<sockaddr*>(&serverHint), sizeof(serverHint)) == SOCKET_ERROR) {
        std::cout << "cannot bind the socket: " << WSAGetLastError() << '\n';
        closesocket(in);
        WSACleanup();
        return 1;
    }

    sockaddr_in client{};
    char buff[buff_size];

    while (isOn) {
        ZeroMemory(&client, sizeof(client));
        int clientLength{ sizeof(client) };
        ZeroMemory(buff, buff_size);

        int bytesIn = recvfrom(
            in,
            buff,
            buff_size,
            0,
            reinterpret_cast<sockaddr*>(&client),
            &clientLength
        );

        if (bytesIn == SOCKET_ERROR) {
            std::cout << "error from client: " << WSAGetLastError() << '\n';
            continue;
        }

        char clientIp[256];
        ZeroMemory(clientIp, 256);
        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
        
        std::string msg(buff, bytesIn);
        msg.pop_back();// adds weird char at the end so remove

         std::cout << "SERVER: message recv from " << clientIp << " : " << buff << '\n';
        // call the method for gui class and let the output handle itself
        outputFn_(msg);
    }

    closesocket(in);
    WSACleanup();
    return 0;
}
