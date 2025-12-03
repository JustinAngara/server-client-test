#pragma once

#include <thread>
#include <atomic>

class KeyListener {

public:
    // create custom controls later
    enum MOVEMENT {
        NONE,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    static void start();
    static void stop();
private:
    static void run();

    static std::atomic_bool running_;
    static std::thread worker_;

    // check for movement directions
    static std::atomic<MOVEMENT> dirState_;
    static std::atomic<MOVEMENT> lastDirState_; // this will be used for optimization
};
