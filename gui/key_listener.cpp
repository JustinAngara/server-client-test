#include "key_listener.h"
#include <iostream>
#include <windows.h>



MOVEMENT updateKeyState(int keyCode) {

    // pressed
    if (GetAsyncKeyState(keyCode) & 0x8000) {
        char keyChar = static_cast<char>(keyCode);

        switch (keyChar) {
        case 'W':
            return MOVEMENT::FORWARD;

        case 'A':
            return MOVEMENT::LEFT;

        case 'S':
            return MOVEMENT::BACKWARD;

        case 'D':
            return MOVEMENT::RIGHT;

        default:
            return MOVEMENT::NONE;
        }

    }
}

// define the static variables
std::atomic_bool KeyListener::running_{ false };
std::thread KeyListener::worker_{};
std::atomic<MOVEMENT> KeyListener::dirState_{ MOVEMENT::NONE };
std::atomic<MOVEMENT> KeyListener::lastDirState_{ MOVEMENT::NONE };

void KeyListener::start() {
    
    if (running_) {
        return; 
    }

    running_ = true;

    worker_ = std::thread([]() { KeyListener::run(); });
}

void KeyListener::stop() {
    if (!running_) {
        return;
    }

    running_ = false;

    if (worker_.joinable()) {
        worker_.join();
    }
}

void KeyListener::run() {
    while (running_) {
        // Iterate through all possible key codes (0 to 255)
        for (int keyCode = 0; keyCode < 256; keyCode++) {

            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                
                char keyChar = static_cast<char>(keyCode);
                
                MOVEMENT newKeyState = updateKeyState(keyCode);

                dirState_ = newKeyState;
                std::cout << static_cast<int>(dirState_.load()) << '\n';
            }
        }
    }
}


