#pragma once

#include <future>

class Server {
public:
    using OutputFn = std::function<void(const std::string&)>;
    explicit Server(OutputFn outputFn = {});

    Server();
    ~Server();

    void start();
    void stop();

private:
    int run(); 
    bool isOn{ false };
    std::future<int> future;
    OutputFn outputFn_;
};
