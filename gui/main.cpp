#include "gui.h"
#include <iostream>
#include <QtWidgets/QApplication>
#include <future>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    gui window;


    window.show();
    return app.exec();
}
