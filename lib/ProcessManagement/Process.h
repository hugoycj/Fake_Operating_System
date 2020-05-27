#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <calculator.h>
#include <vector>
class Process
{
public:
    Process(vector<double> in_A, vector<double> in_B, string type)
    {
        A = in_A;
        B = in_B;
        calculate_type = type;
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
