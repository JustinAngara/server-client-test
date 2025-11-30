#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "client.h"
#include "server.h"
#include <string>


class gui : public QMainWindow {
    Q_OBJECT

public:
    explicit gui(QWidget* parent = nullptr);
    ~gui();

private slots:
    void appendOutputArea(const std::string& text);
    void onInputAreaChanged();
private:
    Ui::guiClass ui;

    Server server_;
    Client client_;
};
