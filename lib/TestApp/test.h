#ifndef TEST_H
#define TEST_H

#include <vector>
#include <random>
#include <calculator.h>
#include <assert.h>
#include <Process.h>
#include <ProcessControlBlock.h>
#include <ProcessesList.h>
#include "gobalPL.h"

using namespace std;
typedef ProcessControlBlock PCB;
using std::default_random_engine;
using std::uniform_int_distribution;

vector<vector<double>> matrix_input(int row, int col);
vector<double> get_one_col(vector<vector<double>> matrix, int col);
vector<double> single_vector_generator(int length);
void test(int mode);

#endif // TEST_H
