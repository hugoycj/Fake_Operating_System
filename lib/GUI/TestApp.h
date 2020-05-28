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
     TestApp(QWidget *parent = 0, ProcessesList *pl = nullptr);

private:
    Ui::TestApp *ui;
    ProcessesList *pl_link = nullptr;
    void clickTestOne();
    void clickTestTwo();
};

#endif // TESTAPP_H
