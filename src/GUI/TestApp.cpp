#include "TestApp.h"
#include "ui_TestApp.h"
#include <QDebug>

TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestApp)
{
    setWindowTitle(tr("Main Window"));
    ui->setupUi(this);
    statusBar() ;
}
