#include "gui.h"
#include "server.h"
#include <iostream>
bool isServerOn{ false };


gui::gui(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.button, &QPushButton::clicked,
        this, &gui::startServer);
}

void gui::startServer() {
    if (!isServerOn) {
        isServerOn = true;
        serverFuture = std::async(std::launch::async, initServer);
    }
    else {
        std::cout << "server is already on\n";
    }
}

gui::~gui() {
    if (serverFuture.valid()) {
        serverFuture.wait();
    }
}
