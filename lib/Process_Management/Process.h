#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <lib/calculator.h>
template <class T1, class T2>
class Process
{
public:
    Process(T1 in_A, T2 in_B, string type)
    {
        A = in_A;
        B = in_B;
        calculate_type = type;
    };

    void run_process()
    {
        if (calculate_type == "mtx_mult")
           mtx_mult(A, B);
        else if (calculate_type == "mtx_inv")
           mtx_inv(A);
        else
           calculate(A, B, calculate_type);
    }

private:
    T1 A;
    T2 B;
    string calculate_type;
};


#endif // PROCESS_H
