/*
 * From line xx to line xx
 * Reference:
 * Ashutosh Kumar, (2017) Adjoint and Inverse of a Matrix [Source code]. https://www.geeksforgeeks.org/adjoint-inverse-matrix/
 */

#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include "calculator.h"
#include "allocator.h"
#include "algorithm"

using namespace std;

/* Basic Arithmetic Operation */
// calculate with the gived data and calculation type
double * calculate(vector<double> data_vec_1, vector<double> data_vec_2, string type) {
    // construct the alloc
    FSB_allocator allocator;
    size_t size = 8;
    double data_1 = data_vec_1[0];
    double data_2 = data_vec_2[0];

    // alloc memory to store value and result
    double * data1_ptr = (double *) allocator.alloc(size);
    double * data2_ptr = (double *) allocator.alloc(size);
    double * res_ptr = (double *) allocator.alloc(size);

    // put specific value into allocated memory
    *data1_ptr = data_1;
    *data2_ptr = data_2;

    // calculate the result
    cout << "Calculation type: " << type << endl;
    if (type == "add") {
        *res_ptr = *data1_ptr + *data2_ptr;
    }

    else if (type == "sub") {
        *res_ptr = *data1_ptr - *data2_ptr;
    }

    else if (type == "div") {
        *res_ptr = *data1_ptr / *data2_ptr;
    }

    else if (type == "mult") {
        *res_ptr = (*data1_ptr) * (*data2_ptr);
    }

    else if (type == "mtx_mult") {
        *res_ptr = mtx_mult(data_vec_1, data_vec_2);
    }

    // dealloc the memory
    allocator.dealloc(data1_ptr, 8);
    allocator.dealloc(data2_ptr, 8);

    cout << "result: " << *res_ptr << endl;
    cout << "" << endl;

    return res_ptr;
}


/* Matrix Operation*/

// 1. Multiplication
// doing dot multiplication
double dot_mult(vector<double> vec1, vector<double> vec2) {
    double result = 0;
    for (unsigned int i = 0; i < vec1.size(); i++) {
        result += vec1[i]*vec2[i];
    }
    return result;
}

// performing matrix mult, calculate the result of dot multiplication of one row and one column
double mtx_mult(vector<double> vec1, vector<double> vec2) {
    // construct the allocator
    FSB_allocator allocator;
    size_t vec_size = sizeof(vector<double>) + 4*(vec1.size());

    // alloc memory to store data and result
    vector<double> * data1_ptr = (vector<double> *) allocator.alloc(vec_size);
    vector<double> * data2_ptr = (vector<double> *) allocator.alloc(vec_size);
    double * res_ptr = (double *) allocator.alloc(8);

    // put data into allocated memory
    *data1_ptr = vec1;
    *data2_ptr = vec2;

    // calculate the result and store the value
    *res_ptr = dot_mult(*data1_ptr, *data2_ptr);

    return *res_ptr;
}


// 2. Inversion
// C++ program to find adjoint and inverse of a matrix
// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(vector<vector<double>> A, vector<vector<double>> & temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Copying into temporary matrix only those element
            // which are not in given row and column
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
n is current dimension of A[][]. */
int determinant(vector<vector<double>> A, int n) {
    int D = 0; // Initialize result

    // Base case : if matrix contains single element
    if (n == 1) {
        return A[0][0];
    }

    // initialize the vector
    vector<double> mid(n,0);
    vector<vector<double>> temp(n,mid);

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}


// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(int N, vector<vector<double>> A, vector<vector<double>> & adj) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    vector<double> mid(N,0);
    vector<vector<double>> temp(N,mid);

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}


// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(int N, vector<vector<double>> A, vector<vector<double>> & inverse) {
    // Find determinant of A[][]
    int det = determinant(A, N);
    if (det == 0) {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // initialize the vector
    vector<double> mid(N,0);
    vector<vector<double>> adj(N,mid);

    // Find adjoint
    adjoint(N, A, adj);

    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            inverse[i][j] = adj[i][j]/double(det);
        }
    }

    return true;
}


// Generic function to display the matrix. We use it to display
// both adjoin and inverse. adjoin is integer matrix and inverse
// is a double.
template<class T>
void display(int N, vector<vector<T>> A) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            cout << setprecision(2) << setw(10) << A[i][j] << " ";
            cout.setf(ios::fixed);
        }
        cout << endl;
    }
}


vector<vector<double>> mtx_inv(vector<vector<double>> matrix) {
    // get dim of matrix
    int N = matrix.size();
    // construct the allocator
    FSB_allocator allocator;

    // caluclate the size of matrixes
    size_t size = sizeof (vector<vector<double>>) + (sizeof(vector<double>))*N + 4*N;

    // allocate memory for variables
    vector<vector<double>> * matrix_ptr = (vector<vector<double>> *) allocator.alloc(size);
    vector<vector<double>> * adj_ptr = (vector<vector<double>> *) allocator.alloc(size);
    vector<vector<double>> * inv_ptr = (vector<vector<double>> *) allocator.alloc(size);

    // store the input matrix into memory
    *matrix_ptr = matrix;

    // initialize the vector variables
    vector<double> mid(N,0);
    vector<vector<double>> adj(N,mid);
    vector<vector<double>> inv(N, mid);


    // display the input matrix
    cout << "Input matrix is :\n";
    display(N, *matrix_ptr);

    // calculate and display the adjoint matrix
    cout << "The Adjoint is :"<<endl;
    adjoint(N, *matrix_ptr, adj);
    *adj_ptr = adj;
    display(N, *adj_ptr);

    // calculate and display the inverse matrix
    cout << "\nThe Inverse is :\n";
    if (inverse(N, *matrix_ptr, inv)) {
        *inv_ptr = inv;
        display(N, *inv_ptr);
    }

    // dealloc the memory
    allocator.dealloc(matrix_ptr,size);
    allocator.dealloc(adj_ptr,size);
    allocator.dealloc(inv_ptr,size);

    return inv;
};
