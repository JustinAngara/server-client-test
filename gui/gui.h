#pragma once

#include <future>
#include <QtWidgets/QMainWindow>
#include "ui_gui.h"   

class gui : public QMainWindow {
    Q_OBJECT 

public:
    gui(QWidget* parent = nullptr);
    ~gui();
    
private slots:


private:
    Ui::guiClass ui;     
    std::future<int> serverFuture;

};
