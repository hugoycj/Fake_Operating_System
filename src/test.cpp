#include <vector>
#include <lib/calculator.h>

using namespace std;
vector<vector<int>> matrix_input(int row, int col);

void test(int mode)
{
    /* Mode 1: Simple Calculation */
    if (mode == 1)
    {

    }
    /* Mode 2: Matrix multiplication */
    else if (mode == 2)
    {
        vector<vector<int>> A, B, C;
        int result_r, result_c;

        A = matrix_input(1, 2);
        B = matrix_input(2, 1);

        result_r = A.size();
        result_c = B[0].size();

        cout << "Size of result is: " << result_c << "*" << result_r;
    }

}


/*
 * @brief Used to get a input matrix
 * @param row #row
 * @param col #col
 * @return the matrix
 */
vector<vector<int>> matrix_input(int row, int col)
{
    vector<vector<int>> matrix;
    vector<int> v;
    matrix.clear();
    int temp=0;
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


/*
 * @brief Used to get a input matrix
 * @param row #row
 * @param col #col
 * @return the matrix
 */
template <class T>
void matrix_split_and_calculate(vector<vector<T>> A, vector<vector<T>> B)
{

};
