
#include "client.h"
#include <winsock2.h>     
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")

bool isClientOn{ false };
std::future<int> clientFuture;

static std::string run() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int initClient() {

    std::cout << "Now in client\n";

    WSADATA data{};
    WORD version{ MAKEWORD(2, 2) };
    int wsOk{ WSAStartup(version, &data) };
    if (wsOk != 0) {
        std::cout << "cant start winsock " << wsOk;
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    std::string input{ run() };
    while (!input.empty()) {

        int sendOk = sendto(
            out,
            input.c_str(),
            static_cast<int>(input.size() + 1),  // <-- fix below
            0,
            reinterpret_cast<sockaddr*>(&server),
            sizeof(server)
        );

        if (sendOk == SOCKET_ERROR) {
            std::cout << "error " << WSAGetLastError() << '\n';
            closesocket(out);
            WSACleanup();
            return 1;
        }

        input = run();
    }

    closesocket(out);
    WSACleanup();
    return 0;
}



void startClient() {
    if (!isClientOn) {
        isClientOn = true;
        clientFuture = std::async(std::launch::async, initClient);
    }
    else {
        std::cout << "client is already on\n";
    }
}
