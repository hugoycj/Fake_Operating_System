#include "lib/mainwindow.h"
#include "ProcessesList.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <ctime>
#include "lib/mapper.h"
#include "lib/allocator.h"
#include "lib/calculator.h"
#include "test.cpp"
#include "Process.h"

/**
 * TODO:
 * 1. 解决输入输出死锁问题
 * 2. 解决进程保存问题
 * 3. 测试进程运行
 */

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
    ProcessesList pl;
    std::cout << "Running" << std::endl;
//    pl.input();
//    pl.display();


    /* memory management Part */
//    calculation_memory_test();

    /* test module */
    thread major(run, &pl);
    thread t1(testAPP, &pl);
    t1.join();
    major.join();
    return 0;
};

void calculation_memory_test() {
    // test basic calculation types
    calculate(-1,2,"add");
    calculate(1,2,"sub");
    calculate(-4,2,"div");
    calculate(100,-2,"mult");
    calculate(10,200,"sub");

    // test matrix calculation types
    vector<double> vec1 = {1, 2, 1};
    vector<double> vec2 = {1, 2, 3};
    mtx_mult(vec1, vec2);

    // test mtx_inv
    vector<vector<int>> A =
    { {5, -2, 2, 7},
      {1, 0, 0, 3},
      {-3, 1, 5, 0},
      {3, -1, -9, 4}};
    mtx_inv(4,A);

    // test mtx_inv with memory expansion
    srand(1);
    int size = 5;
    vector<vector<int>> B;
    for (int x=0; x<size; x++) {
        vector<int> buf;
        for (int y=0; y < size; y++) {
            buf.push_back(int((rand() % (63-0+1)) + 0));
        }
        B.push_back(buf);
    }
    mtx_inv(size,B);
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
    int i = 0;
    int lastTime = 0;

    while (1)
    {
        int now = clock()/CLOCKS_PER_SEC;
        if (now - lastTime > 0)
        {
            if (!pl->isEmpty())
            {
                pl->output();
                cout << "runed a process" << endl;
                sleep(2);
            }
            pl->display();
            lastTime = now;
        }
    }

    while (1)
    {

        sleep(2);
    }
}

//void display_pl(ProcessesList *pl)
//{
//    int i = 0;
//    int lastTime = 0;

//    while (1)
//    {
//        int now = clock()/CLOCKS_PER_SEC;
//        if (now - lastTime > 0)
//        {
//          pl->display();
//          lastTime = now;
//        }
//    }
//}
