#ifndef LOGGER_H
#define LOGGER_H
#include<QPlainTextEdit>
#include<QPointer>
#include<QString>
#include<string>

class logger{

private:
    QPointer<QPlainTextEdit> _textEdit;
public:
    void out(std::string output);
    void set(QPlainTextEdit *textEdit);
};



#endif // LOGGER_H
