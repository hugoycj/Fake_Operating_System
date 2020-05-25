#include <vector>
#include <lib/calculator.h>
#include <assert.h>
#include <Process.h>
#include <ProcessControlBlock.h>

using namespace std;
typedef ProcessControlBlock PCB;

vector<vector<double>> matrix_input(int row, int col);
vector<double> get_one_col(vector<vector<double>> matrix, int col);

/*
 * @brief Used to test memory allocator and process management
 * @param mode
 * One test function is one process, it include: creating process and PCB
 */
void test(int mode)
{
    /* Mode 1: Simple Calculation */
    if (mode == 1)
    {

    }
    /* Mode 2: Matrix multiplication */
    else if (mode == 2)
    {
        vector<double> tempA, tempB;
        int size;

//        vector<vector<double>> A, B, C;
//        A = matrix_input(1, 3);
//        B = matrix_input(3, 1);
//        result_r = A.size();
//        result_c = B[0].size();
//        cout << "Size of result is: " << result_c << "*" << result_r << endl;
//        tempA = A[0];
//        tempB = get_one_col(B, 1);

        tempA = {1, 2, 1};
        tempB = {1, 2, 3};
        size = sizeof(tempA);

        static Process<vector<double>, vector<double>, double>  p1(tempA, tempB, "mtx_mult");
        double (*Process<vector<double>, vector<double>, double>::pf1)() = p1.run_process();//普通的函数指针
//        PCB pcb1('mtx_mult', size, p1);
    }
    /* Mode 3: Matrix invert */
    else if (mode == 3)
    {
        vector<vector<double>> A, result;
        A = { {5, -2, 2, 7},
             {1, 0, 0, 3},
             {-3, 1, 5, 0},
             {3, -1, -9, 4}};
        static Process<vector<vector<double>>, int, vector<vector<double>>>  P2(A, 0, "mtx_inv");
    }
}


/*
 * @brief Used to get a input matrix
 * @param row #row
 * @param col #col
 * @return the matrix
 */
vector<vector<double>> matrix_input(int row, int col)
{
    vector<vector<double>> matrix;
    vector<double> v;
    matrix.clear();
    double temp=0;
    cout << "Please input a " << row << "*" << col << " matrix:" << endl;
    for (int i = 0; i < row; i++)
    {
        v.clear();//子数组返回时要清除
        for (int j = 0; j < col; j++)
        {
            cin >> temp;
            v.push_back(temp);

        }
        matrix.push_back(v);
    }

    cout << "The Matrix is:" << endl;
    for (int i = 0; i < row; i++)//打印输入的二维数组
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix[i][j] << " ";

        }
        printf("\n");
   }

   return matrix;
};

vector<double> get_one_col(vector<vector<double>> matrix, int col)
{
    vector<double> result;
    int r,i,c;
    double temp;

    r = matrix.size();
    c = matrix[0].size();
    for (i = 0; i < r; i++)
    {
        temp = matrix[i][col-1];
        result.push_back(temp);
    }

    assert(result.size() == r);
    return result;
}
