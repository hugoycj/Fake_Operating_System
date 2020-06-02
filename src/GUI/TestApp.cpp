#include "TestApp.h"
#include "ui_testapp.h"
#include <QDebug>
#include <iostream>
#include "test.h"


TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestApp)
{
    setWindowTitle(tr("Test App"));
    ui->setupUi(this);
    connect(ui->testOne, &QPushButton::clicked,this, &TestApp::clickTestOne);
    connect(ui->testTwo, &QPushButton::clicked,this, &TestApp::clickTestTwo);
}

void TestApp::clickTestOne()
{
    std::cout << "Clicked Test One" << std::endl;
    test(1);
}

void TestApp::clickTestTwo()
{
    std::cout << "Clicked Test Two" << std::endl;
    test(2);
}
