#pragma once

#include <future>

class Server {
public:
    Server();
    ~Server();

    void start();
    void stop();

private:
    int run(); 

    bool isOn{ false };
    std::future<int> future;
};
