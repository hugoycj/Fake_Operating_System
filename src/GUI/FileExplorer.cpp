#include "fileexplorer.h"
#include "ui_fileexplorer.h"
#include <iostream>

fileexplorer::fileexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fileexplorer)
{
    ui->setupUi(this);
    setWindowTitle("File Explorer");

}

fileexplorer::~fileexplorer()
{
    delete ui;
}

void fileexplorer::on_BackButton_clicked()
{
    std::cout << "BackButton Clicked" << std::endl;
    // cd ..
}
