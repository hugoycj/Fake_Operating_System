#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <calculator.h>
#include <vector>
class Process
{
public:
    int size;
    Process(vector<double> in_A, vector<double> in_B, string type, int in_size)
    {
        A = in_A;
        B = in_B;
        calculate_type = type;
        size = in_size;
    };

    void run_process()
    {
        double *result;
        result = calculate(A, B, calculate_type);
        cout << result << endl;
    }

private:
    vector<double> A;
    vector<double> B;
    string calculate_type;
};



#endif // PROCESS_H
