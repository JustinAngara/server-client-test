//#include "server.h"
#include "client.h"
#include "server.h"
#include "gui.h"


gui::gui(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.button, &QPushButton::clicked,
        this, [this]() { server_.start();  });
    connect(ui.button2, &QPushButton::clicked,
        this, [this]() { client_.start(); });
}

gui::~gui() {
    server_.stop();

}
