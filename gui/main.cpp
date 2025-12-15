#include "gui.h"
#include "key_listener.h"
#include <iostream>


int main(int argc, char* argv[]) {
    int x = 5;

    KeyListener::start();

    QApplication app(argc, argv);
    gui window;



    window.show();
    return app.exec();
}


