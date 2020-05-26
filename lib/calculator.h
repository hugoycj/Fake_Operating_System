#include <iostream>
#include <vector>
using namespace std;

/*
 * The input of testfile would be an long arithmetic formula
 * e.g. "(1/2) + (2*3)
 * or even more complicated one
 * e.g. (matrixA * matrix_B) + (inverse(matrix_C))"

 * the formula will go through a decoder and are divided into small arithmetic unit (call AU here)
 * e.g. (2*3)
 * one AU is treated as one new prcoess in our simulation, which is under the control of process manager


 * Function: calculate
 * the calculator will take in the data of each process (i.e. AU) and the type of AU as input
 * in calculate() function, data will be stored through our own memory allocator
 * during the calculation process,
 * intermediate variable will be created and stored in the region the allocator assigned
 * after using mid variables, they will be deallocated by our memory allocator
 * the result will also be stored somewhere, and the ptr tof the result will be returned
 */

/* Basic Arithmetic Operation */

// calculate with the gived data and calculation type
// add, sub, div, mult, mtx_mult
double * calculate(vector<double> data_vec_1, vector<double> data_vec_2, string type);

/* Matrix Operation */
// matrix inverse
vector<vector<double>> mtx_inv(vector<vector<double>> A);
