#include "test.h"

/*
 * @brief Used to test memory allocator and process management
 * @param mode
 * One test function is one process, it include: creating process and PCB
 */
void test(int mode)
{
    string type;
    int size;
    int cur_id;
    cur_id = global_pl.get_cur_id();
    vector<double> tempA, tempB;

    srand( (unsigned)time( NULL ) );
    size = rand()%9 + 1;
    cout << "Generate a matrix of size: " << size << endl;

    vector<string> type_set = {"add", "sub", "div", "mult"};

    /* Mode 1: Simple Calculation */
    if (mode == 1)
    {
        // select the calculation type
        int num = rand() % (3-0+1);
        type = type_set[num];
        cout<<"type: "<<type<<endl;

        tempA = single_vector_generator(1);
        tempB = single_vector_generator(1);
        size = 1;
        static Process p0(tempA, tempB, type, size);
        PCB pcb2(cur_id, type, size, &p0);
        global_pl.push(pcb2);
    }

    /* Mode 2: Matrix multiplication */
    else if (mode == 2)
    {
        type ="mtx_mult";

        tempA = single_vector_generator(size);
        tempB = single_vector_generator(size);
        size = sizeof(tempA);

        static Process p1(tempA, tempB, type, size);
        PCB pcb1(cur_id, type, size, &p1);
        global_pl.push(pcb1);

    }

    global_pl.display();
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
        // sub vector should be clear when return
        v.clear();
        for (int j = 0; j < col; j++)
        {
            cin >> temp;
            v.push_back(temp);

        }
        matrix.push_back(v);
    }

    // print out the input matrix
    cout << "The Matrix is:" << endl;
    for (int i = 0; i < row; i++)
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
