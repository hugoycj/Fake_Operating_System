#include "logger.h"

void logger::out(std::string output) {
    this-> _textEdit->appendPlainText(QString::fromStdString(output));
};

void logger::set(QPlainTextEdit *textEdit) {
    this->_textEdit = textEdit;
}

