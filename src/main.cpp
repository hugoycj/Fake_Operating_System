#include "lib/mainwindow.h"
#include "ProcessesList.h"
#include <QApplication>
#include <iostream>

#include "lib/allocator.h"
#include "lib/mapper.h"

void memory_management_test();

int main(int argc, char *argv[])
{
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
    memory_management_test();
}

void memory_management_test() {
        // construct allocator
        FSB_allocator a1;

        // test the number of remaining blocks in 8-byte block set
        // allocate a 8-byte memory block
        a1.alloc(3);
        assert(a1.loop_test(0) == 15);
        a1.alloc(7);
        assert(a1.loop_test(0) == 14);
        a1.alloc(8);
        assert(a1.loop_test(0) == 13);

        int * ptr = (int *) a1.alloc(8);
        a1.dealloc(ptr);
        assert(a1.loop_test(0) == 13);

    //    // test 16-bytes block
    //    a1.alloc(9);
    //    assert(a1.loop_test(1) == 15);
    //    a1.alloc(15);
    //    assert(a1.loop_test(1) == 14);
    //    a1.alloc(16);
    //    assert(a1.loop_test(1) == 13);

    //    int * ptr2 = (int *) a1.alloc(14);
    //    a1.dealloc(ptr2);
    //    assert(a1.loop_test(1) == 13);

    //    // test 32-bytes block
    //    a1.alloc(17);
    //    assert(a1.loop_test(2) == 15);
    //    a1.alloc(31);
    //    assert(a1.loop_test(2) == 14);
    //    a1.alloc(32);
    //    assert(a1.loop_test(2) == 13);

    //    a1.alloc(2047);
    //    assert(a1.loop_test(8) == 15);
    //    a1.alloc(2048);
    //    assert(a1.loop_test(8) == 14);

    //    a1.alloc(4097);
    //    assert(a1.loop_test(9) == 15);
    //    a1.alloc(5152);
    //    assert(a1.loop_test(9) == 14);
    //    a1.alloc(8192);
    //    assert(a1.loop_test(9) == 13);

    //    a1.alloc(2049);
    //    assert(a1.loop_test(10) == 15);
    //    a1.alloc(4095);
    //    assert(a1.loop_test(10) == 14);
    //    a1.alloc(4096);
    //    assert(a1.loop_test(10) == 13);
//        VM m1;
//        m1.mapper();
        cout<<"Pass test"<<endl;
}
