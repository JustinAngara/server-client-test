#pragma once

#include <future>
#include <string>

class Client {
public:
    Client(const std::string& serverIp = "127.0.0.1", unsigned short port = 54000);
    ~Client();

    void start();   // <-- this is what you will call: client.start()
    void stop();    // optional, for later cleanup/extending

private:
    int run();      // worker function (old initClient logic)

    std::string serverIp_;
    unsigned short port_;

    bool isOn_{ false };
    std::future<int> future_;
};
