#pragma once

#include <future>

class Server {
public:
    // we are able to create a alias for references to teh gui
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
