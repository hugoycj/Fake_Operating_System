#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtGui>
#include "fileexplorer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int current_line_num = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void clickTextbook();
    void clickFile();
    void clickMD();
    void clickTestApp();
    void clickAC();
    void clickCalender();

};
#endif // MAINWINDOW_H
