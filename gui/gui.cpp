
#include <QPushButton>
#include <QTextEdit>
#include "gui.h"

gui::gui(QWidget* parent)
// in order to connect the method shared between client and gui
    : QMainWindow(parent), server_([this](const std::string& text) { // this is outputfn_ we are passing into
        QMetaObject::invokeMethod(this,
            [this, text]() { appendOutputArea(text); },
            Qt::QueuedConnection
        );
    }, 54004),
    client_("127.0.0.1", 54004) { // use 127.0.0.1

    ui.setupUi(this);

    // anon functions with passing in this will refer back to gui class
    connect(ui.button,  &QPushButton::clicked,
            this, [this]() { server_.start(); });

    connect(ui.button2, &QPushButton::clicked,
            this, [this]() { client_.start(); });

    connect(ui.submit, &QPushButton::clicked,
        this, [this]() { 
            client_.sendMessage(gui::text_); 
            ui.inputArea->clear();
        });

    connect(ui.inputArea, &QTextEdit::textChanged,
            this, &gui::onInputAreaChanged);
    
}

void gui::onInputAreaChanged() {
    gui::text_ = ui.inputArea->toPlainText().toStdString();
    
}

void gui::appendOutputArea(const std::string &text) {
    ui.outputArea->append(QString::fromStdString(text));
}

gui::~gui() {
    server_.stop();
    client_.stop();

}
