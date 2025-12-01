#include "gui.h"
#include "key_listener.h"
#include <iostream>
int main(int argc, char* argv[]) {

    KeyListener::start();

    QApplication app(argc, argv);
    gui window;

    window.show();
    return app.exec();
}


