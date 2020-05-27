#include "mainwindow.h"
#include "TextEditor.h"
#include "MappingDisplayer.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QHeaderView>
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
    QIcon TextIcon;
    TextIcon.addFile(tr(":/image/icon/TextBook.ico"));
    ui->TextbookButton->setIcon(TextIcon);
    ui->TextbookButton->setIconSize(QSize(50,50));
    connect(ui->TextbookButton, &QPushButton::clicked,this, &MainWindow::clickTextbook);
    ui->TextbookLabel->setStyleSheet("color:white;");

    /// Set textbook icon
    QIcon FileIcon;
    FileIcon.addFile(tr(":/image/icon/FileEplorer.ico"));
    ui->FileButton->setIcon(FileIcon);
    ui->FileButton->setIconSize(QSize(50,50));
    connect(ui->FileButton, &QPushButton::clicked,this, &MainWindow::clickFile);
    ui->FileLabel->setStyleSheet("color:white;");

    /// Set memory_displayer icon
    QIcon MemoryIcon;
    MemoryIcon.addFile(tr(":/image/icon/MemoryDisplayer.ico"));
    ui->DisplayerButton->setIcon(MemoryIcon);
    ui->DisplayerButton->setIconSize(QSize(50,50));
    connect(ui->DisplayerButton, &QPushButton::clicked,this, &MainWindow::clickMemory);
    ui->DisplayerLabel->setStyleSheet("color:white;");

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
//    long * s;
}

void MainWindow::clickFile()
{
    std::cout << "Clicked File Explorer" << std::endl;
//    a->show();
}

void MainWindow::clickMemory()
{
    std::cout << "Clicked Memory Displayer" << std::endl;
//    Qt::WindowFlags m_flags = windowFlags();
    MappingDisplayer *t = new MappingDisplayer(current_line_num);

    current_line_num++;
//    t->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
//    t->show();
}

