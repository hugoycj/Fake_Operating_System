#include "lib/mainwindow.h"
#include "ProcessesList.h"
#include <QApplication>
#include <iostream>

#include "lib/mapper.h"
#include "lib/allocator.h"
#include "lib/calculator.h"

void calculation_memory_test();

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
//    pl.input();
//    pl.display();


    /* memory management Part */
    calculation_memory_test();

    return 0;
};

void calculation_memory_test() {
    // test basic calculation types
    vector<double> a = {-100};
    vector<double> b = {2};
    calculate(a, b, "mult");
//    calculate(-1,2,"add");
//    calculate(1,2,"sub");
//    calculate(-4,2,"div");
//    calculate(100,-2,"mult");
//    calculate(10,200,"sub");

    // test matrix calculation types
    vector<double> vec1 = {1, 2, 1};
    vector<double> vec2 = {1, 2, 3};
//    mtx_mult(vec1, vec2);
    calculate(vec1, vec2, "mtx_mult");

//    // test mtx_inv
//    vector<vector<double>> A =
//    { {5, -2, 2, 7},
//      {1, 0, 0, 3},
//      {-3, 1, 5, 0},
//      {3, -1, -9, 4}};
//    mtx_inv(A);

//    // test mtx_inv with memory expansion
//    srand(1);
//    int size = 5;
//    vector<vector<double>> B;
//    for (int x=0; x<size; x++) {
//        vector<double> buf;
//        for (int y=0; y < size; y++) {
//            buf.push_back(double((rand() % (63-0+1)) + 0));
//        }
//        B.push_back(buf);
//    }
//    mtx_inv(B);
};


