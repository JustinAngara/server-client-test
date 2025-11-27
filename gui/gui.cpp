//#include "server.h"
#include "client.h"
#include "gui.h"





gui::gui(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.button, &QPushButton::clicked,
        this, []() {
        });
    connect(ui.button2, &QPushButton::clicked,
        this, []() { startClient(); });
}




gui::~gui() {
    //if (serverFuture.valid()) {
    //    serverFuture.wait();
    //}
    //if (clientFuture.valid()) {
    //    clientFuture.wait();
    //}
}
