
#include <QPushButton>
#include <QTextEdit>
#include "gui.h"

gui::gui(QWidget* parent)
// in order to connect the method shared between client and gui
    : QMainWindow(parent), server_([this](const std::string& text) {
        QMetaObject::invokeMethod(this,
            [this, text]() { appendOutputArea(text); },
            Qt::QueuedConnection
        );
    }) {

    ui.setupUi(this);

    connect(ui.button,  &QPushButton::clicked,
            this, [this]() { server_.start(); });

    connect(ui.button2, &QPushButton::clicked,
            this, [this]() { client_.start(); });

    connect(ui.inputArea, &QTextEdit::textChanged,
            this, &gui::onInputAreaChanged);
    
}

void gui::onInputAreaChanged() {
    std::string text = ui.inputArea->toPlainText().toStdString();
    
}

void gui::appendOutputArea(const std::string &text) {
    ui.outputArea->append(QString::fromStdString(text));
}

gui::~gui() {
    server_.stop();
}
