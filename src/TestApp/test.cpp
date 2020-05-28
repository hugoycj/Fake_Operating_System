#include "test.h"


/*
 * @brief Used to test memory allocator and process management
 * @param mode
 * One test function is one process, it include: creating process and PCB
 */
void test(int mode, ProcessesList *pl)
{
    string type;
    int size;
    int cur_id;
    cur_id = pl->get_cur_id();
    vector<double> tempA, tempB;

    srand( (unsigned)time( NULL ) );
    size = rand()%9 + 1;
    cout << "Generate a matrix of size: " << size << endl;
    /* Mode 1: Simple Calculation */
    if (mode == 1)
    {
        type ="mult";
        tempA = single_vector_generator(1);
        tempB = single_vector_generator(1);
        size = 1;
        static Process p0(tempA, tempB, type);
        PCB pcb2(cur_id, type, size, &p0);
        pl->push(pcb2);
    }
    /* Mode 2: Matrix multiplication */
    else if (mode == 2)
    {
        type ="mtx_mult";

        tempA = single_vector_generator(size);
        tempB = single_vector_generator(size);
        size = sizeof(tempA);

        static Process p1(tempA, tempB, type);
        PCB pcb1(cur_id, type, size, &p1);
        pl->push(pcb1);
    }
    /* Mode 3: Matrix invert */
//    else if (mode == 3)
//    {
//        type = "mtx_inv";
//        vector<vector<double>> A, result;
//        A = { {5, -2, 2, 7},
//             {1, 0, 0, 3},
//             {-3, 1, 5, 0},
//             {3, -1, -9, 4}};
//        size = A.size()^2;
//        static Process<vector<vector<double>>, int, vector<vector<double>>>  P2(A, 0, "mtx_inv");
//        PCB pcb2(cur_id, type, size);
//        pl->push(pcb2);
//    }
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

vector<double> single_vector_generator(int length)
{
    vector<double> v;
    double temp=0;
    v.clear();
    for (int j = 0; j < length; j++)
    {
        srand( (unsigned)time( NULL ) );
        temp = rand()%10;
        v.push_back(temp);

    }

    cout << "The Matrix is:" << endl;
    for (int j = 0; j < length; j++)
    {
        cout << v[j] << " ";

    }
    printf("\n");

   return v;
}
