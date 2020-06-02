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
#include "Process.h"
#include "TestApp.h"

using namespace std;
void memory_expansion_test();

int main(int argc, char *argv[]) {

    /* termianl testing section for memory allocation with expansion */
//    memory_expansion_test();

    /* Desktop GUI Part*/
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Fake Operating System");
    w.show();
    return a.exec();

};


void memory_expansion_test() {

    cout << "***************** Memory expansion test *****************" << endl;
    // test mtx_inv with memory expansion
    srand(1);
    int size = 4;
    vector<vector<double>> B;
    for (int x=0; x<size; x++) {
        vector<double> buf;
        for (int y=0; y < size; y++) {
            buf.push_back(double((rand() % (63-0+1)) + 0));
        }
        B.push_back(buf);
    }
    mtx_inv(B);
    cout << "*********************** Finish test ***********************" << endl;
};
