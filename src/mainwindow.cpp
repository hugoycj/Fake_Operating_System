#include "lib/mainwindow.h"
#include "lib/TextEditor.h"
#include "ui_mainwindow.h"
#include <QIcon>   //注意包含头文件
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /// Set background
    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow{border-image:url(:/image/background.jpg);}");

    /// Set textbook icon
    ui->setupUi(this);
    QIcon TextIcon; //新建QIcon对象
    TextIcon.addFile(tr(":/image/icon/TextBook.ico")); //让QIcon对象指向想要的图标
    ui->TextbookButton->setIcon(TextIcon); //给按钮添加图标
    ui->TextbookButton->setIconSize(QSize(50,50));//重置图标大小
    connect(ui->TextbookButton, &QPushButton::clicked,this, &MainWindow::clickTextbook);
    ui->TextbookLabel->setStyleSheet("color:white;");

    /// Set textbook icon
    QIcon FileIcon; //新建QIcon对象
    FileIcon.addFile(tr(":/image/icon/FileEplorer.ico")); //让QIcon对象指向想要的图标
    ui->FileButton->setIcon(FileIcon); //给按钮添加图标
    ui->FileButton->setIconSize(QSize(50,50));//重置图标大小
    connect(ui->FileButton, &QPushButton::clicked,this, &MainWindow::clickFile);
    ui->FileLabel->setStyleSheet("color:white;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickTextbook()
{
    std::cout << "Clicked Textbook" << std::endl;
    Qt::WindowFlags m_flags = windowFlags();
    TextEditor *t = new TextEditor(this);
    t->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    t->show();
    long * s;
}

void MainWindow::clickFile()
{
    std::cout << "Clicked File Explorer" << std::endl;
//    a->show();
}

