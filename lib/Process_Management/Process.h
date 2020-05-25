#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <lib/calculator.h>

template <class T1, class T2, class T3>
class Process
{
public:
    Process(T1 in_A, T2 in_B, string type)
    {
        A = in_A;
        B = in_B;
        calculate_type = type;
    };

    T3 run_process(T1 in_A, T2 in_B, string type)
    {
        T3 result;
        if (calculate_type == "mtx_mult")
//TODO: fix bug
//           result = mtx_mult(A, B);
            std::cout << "pass" << endl;
        else if (calculate_type == "mtx_inv")
//           result = mtx_inv(2, A);
            std::cout << "pass" << endl;
        else
//           result = calculate(A, B, calculate_type);
            std::cout << "pass" << endl;
        return result;
    }

private:
    T1 A;
    T2 B;
    string calculate_type;
};



#endif // PROCESS_H
