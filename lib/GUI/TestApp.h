#ifndef TESTAPP_H
#define TESTAPP_H
#include <QMainWindow>
namespace Ui {
    class TestApp;
}
class TestApp : public QMainWindow
{
    Q_OBJECT

public:
     TestApp(QWidget *parent = 0);
//     ~TestApp();
private:
    Ui::TestApp *ui;
};

#endif // TESTAPP_H
