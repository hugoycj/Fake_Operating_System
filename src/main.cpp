#include "mainwindow.h"
#include "ProcessesList.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <ctime>
#include "mapper.h"
#include "allocator.h"
#include "calculator.h"
#include "src/TestApp/test.cpp"
#include "Process.h"
#include "TestApp.h"

using namespace std;
void calculation_memory_test();
void testAPP(ProcessesList *pl);
void run(ProcessesList *pl);
void display_pl(ProcessesList *pl);

int main(int argc, char *argv[]) {

    /* Desktop GUI Part*/
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.setWindowTitle("Fake Operating System");
//    w.show();
//    return a.exec();

    /* Process Management Test Part*/
//    ProcessesList pl;
//    std::cout << "Running" << std::endl;
//    test(1, &pl);
//    test(1, &pl);
//    test(2, &pl);
//    test(2, &pl);
//    test(2, &pl);
//    test(2, &pl);
//    thread major(run, &pl);
//    thread t1(testAPP, &pl);
//    thread dpl(display_pl, &pl);
//    t1.join();
//    dpl.join();
//    major.join();

//    calculation_memory_test();
    return 0;
};

void testAPP(ProcessesList *pl)
{
    int mode;
    while(1)
    {
//        cout << "Please input test mode: ";
        cin >> mode;
        if (mode == 0)
            return;
        else
            test(mode, pl);
    }
}

void run(ProcessesList *pl)
{
//    int i = 0;
    int lastTime = 0;

    while (1)
    {
        int now = clock()/(CLOCKS_PER_SEC+1);
        if (now - lastTime > 0)
        {
            pl->display();
            if (!pl->isEmpty())
            {
                pl->output();
                cout << "runed a process" << endl;
                sleep(2);
            }
            lastTime = now;
        }
    }
}

void display_pl(ProcessesList *pl)
{
//    int i = 0;
    int lastTime = 0;

    while (1)
    {
        int now = clock()/CLOCKS_PER_SEC;
        if (now - lastTime > 0)
        {
            pl->display();
            lastTime = now;
        }
    }
};

void calculation_memory_test() {
    for (int i = 0; i < 10; i++) {
        cout << "**********************: " << i << endl;
        vector<double> A = {1, 2, 1};
        vector<double> B = {1, 2, 2};
        calculate(A,B,"mtx_mult");
//        static Process p1(A, B, "mtx_mult");
//        p1.run_process();
    };
};

