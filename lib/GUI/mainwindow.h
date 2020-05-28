#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtGui>
#include "ProcessesList.h"

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
    ProcessesList pl;
    void clickTextbook();
    void clickFile();
    void clickMemory();
    void clickTestApp();
};
#endif // MAINWINDOW_H
