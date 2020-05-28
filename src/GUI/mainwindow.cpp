#include "mainwindow.h"
#include "TextEditor.h"
#include "MappingDisplayer.h"
#include "activitymonitor.h"
#include "TestApp.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QIcon>
#include <iostream>
#include "gobalPL.h"

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

    /// Set file explorer icon
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

    /// Set TestApp icon
    QIcon TestIcon;
    TestIcon.addFile(tr(":/image/icon/MemoryDisplayer.ico"));
    ui->TestAppButton->setIcon(TestIcon);
    ui->TestAppButton->setIconSize(QSize(50,50));
    connect(ui->TestAppButton, &QPushButton::clicked,this, &MainWindow::clickTestApp);
    ui->TestAppLabel->setStyleSheet("color:white;");


    /// Set AC icon
    QIcon ACIcon;
    ACIcon.addFile(tr(":/image/icon/MemoryDisplayer.ico"));
    ui->ACButton->setIcon(ACIcon);
    ui->ACButton->setIconSize(QSize(50,50));
    connect(ui->ACButton, &QPushButton::clicked,this, &MainWindow::clickAC);
    ui->ACLabel->setStyleSheet("color:white;");

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
}

void MainWindow::clickTestApp()
{
    std::cout << "Clicked TestApp" << std::endl;
    Qt::WindowFlags m_flags = windowFlags();
    TestApp *t = new TestApp(this);
    t->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    t->show();
}

void MainWindow::clickFile()
{
    std::cout << "Clicked File Explorer" << std::endl;
    Qt::WindowFlags m_flags = windowFlags();
    fileexplorer *fe = new fileexplorer(this);
    fe->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    fe->show();
}

void MainWindow::clickMemory()
{
    std::cout << "Clicked Memory Displayer" << std::endl;
    MappingDisplayer *t = new MappingDisplayer();
    t->close();
}

void MainWindow::clickAC()
{
    std::cout << "Clicked Activity Monitor" << std::endl;
    Qt::WindowFlags m_flags = windowFlags();
    activitymonitor *ac = new activitymonitor(this);
    ac->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    ac->show();


    /*
     * test_process_end(process_list);
     *
     * int count_test_times = 0;
     * ProcessesList pl;
     * while (true) {
     *      if (count_test_times = 0) {
     *          //    test(1, &pl);
                //    test(1, &pl);
                //    test(2, &pl);
                //    test(2, &pl);
                //    test(2, &pl);
                //    test(2, &pl);
            } else {

         *      if (test_process_end()) {
         *          ui->ACTable->clearitem();
         *      }
         *
         *      if (new_process_add_in_flag/input_change) {
         *          test(input_mode);
         *          new_p_id_item = ....
         *          new_p_priority_item = ....
         *          ...
         *          ui->ACTable->setitem(r,c,item)
         *      }
         *
         *      if (input == "quit") {
         *          break;
         *      }
     *      }
     *  count++;
     *  }
     *
     */
}
