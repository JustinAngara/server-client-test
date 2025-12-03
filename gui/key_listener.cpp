#include "key_listener.h"
#include <iostream>
#include <windows.h>

// define the static variables
std::atomic_bool KeyListener::running_{ false };
std::thread KeyListener::worker_{};
std::atomic<MOVEMENT> KeyListener::dirState_{ MOVEMENT::NONE };
std::atomic<MOVEMENT> KeyListener::lastDirState_{ MOVEMENT::NONE };

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
    int A{ static_cast<int>('A') }, Z{ static_cast<int>('Z') };

    while (running_) {
        // iterate through the [A-Z]
        for (int keyCode = A; keyCode <= Z; keyCode++) {

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


