#include "lib/mainwindow.h"
#include "ProcessesList.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    /* Desktop GUI Part*/
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.setWindowTitle("Fake Operating System");

//    w.show();
//    return a.exec();

    /* Process Management Test Part*/
    ProcessesList pl;
    std::cout << "Running" << std::endl;
    pl.input();
    pl.display();
    /** TODO:
     *  while (!pl.isempty)
     *   Process *PCB = pl.output();
     *   rl = *PCB;
     *   rl.run();
     *   rl.state = "F"
     */



}
