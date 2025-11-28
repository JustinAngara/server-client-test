#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "client.h"
#include "server.h"

class gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui(QWidget* parent = nullptr);
    ~gui();

private:
    Ui::guiClass ui;

    Server server_;
    Client client_;   
};
