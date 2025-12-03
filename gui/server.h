#pragma once

#include <future>
#include <functional>
class Server {
public:
    // we are able to create a alias for references to teh gui
    using OutputFn = std::function<void(const std::string&)>;
    explicit Server(OutputFn outputFn = nullptr, unsigned short port = 54000);

    ~Server();

    void start();
    void stop();

private:
    int run(); 
    bool isOn{ false };
    std::future<int> future;

    OutputFn outputFn_;
    unsigned short port_;
};
