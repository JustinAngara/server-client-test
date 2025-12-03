#include "key_listener.h"
#include <iostream>
#include <windows.h>

// define the static variables
std::atomic_bool KeyListener::running_{ false };
std::thread KeyListener::worker_{};
std::atomic<KeyListener::MOVEMENT> KeyListener::dirState_{ KeyListener::NONE };
std::atomic<KeyListener::MOVEMENT> KeyListener::lastDirState_{ KeyListener::NONE };

KeyListener::MOVEMENT updateKeyState(int keyCode) {

    // pressed
    if (GetAsyncKeyState(keyCode) & 0x8000) {
        char keyChar = static_cast<char>(keyCode);

        
        switch (keyChar) {
            // focus on the movement side
            case 'W':
                return KeyListener::FORWARD;

            case 'A':
                return KeyListener::LEFT;

            case 'S':
                return KeyListener::BACKWARD;

            case 'D':
                return KeyListener::RIGHT;

            default:
                return KeyListener::NONE;
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
            
                // std::cout << static_cast<int>(dirState_.load()) << '\n';
            
            }
        }
    }
}


