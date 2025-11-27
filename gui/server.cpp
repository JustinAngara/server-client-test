#include "server.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")
bool isServerOn{ false };
std::future<int> serverFuture;


int initServer() {
    std::cout << "Now in server \n";

    const int buff_size{ 1024 };

    WSADATA data{};
    WORD version{ MAKEWORD(2, 2) };


    int wsOk{ WSAStartup(version, &data) };
    if (wsOk != 0) {
        std::cout << "cant start winsock " << wsOk << '\n';
        return 1;
    }


    // we create a socket dgram which is going to bind to a port
    SOCKET in{ socket(AF_INET, SOCK_DGRAM, 0) };
    if (in == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << '\n';
        WSACleanup();
        return 1;
    }

    // 54000 is the port that the socket will bind to
    sockaddr_in serverHint{};
    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(54000);

    // we perform it, if it fails we want to perform a cleanup
    if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
        std::cout << "cannot bind the socket: " << WSAGetLastError() << '\n';
        closesocket(in);
        WSACleanup();
        return 1;
    }


    // we will wait for the client to send a message and recieve from
    sockaddr_in client{};
    char buff[buff_size];

    while (true) { // continuosly lsiten

        ZeroMemory(&client, sizeof(client));
        int clientLength{ sizeof(client) };
        ZeroMemory(buff, buff_size);


        // recv function, this will be the blocking call
        int bytesIn = recvfrom(
            in,
            buff,
            buff_size,
            0,
            (sockaddr*)&client,
            &clientLength
        );

        //std::cout << "this is the number of bytes in " << bytesIn << '\n';
        if (bytesIn == SOCKET_ERROR) {
            std::cout << "error from client: " << WSAGetLastError() << '\n';
            continue;
        }

        char clientIp[256];
        ZeroMemory(clientIp, 256);
        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

        std::cout << "SERVER: message recv from " << clientIp << " : " << buff << '\n';
    }
    closesocket(in);
    WSACleanup();
    return 0;

}


void startServer() {
    if (!isServerOn) {
        isServerOn = true;
        serverFuture = std::async(std::launch::async, initServer);
    }
    else {
        std::cout << "server is already on\n";
    }
}