#ifndef TESTAPP_H
#define TESTAPP_H
#include <QMainWindow>
#include "ProcessesList.h"

namespace Ui {
    class TestApp;
}
class TestApp : public QMainWindow
{
    Q_OBJECT

public:
     TestApp(QWidget *parent = 0);

private:
    Ui::TestApp *ui;
    void clickTestOne();
    void clickTestTwo();
};

#endif // TESTAPP_H
