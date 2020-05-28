/*
 * File: tools.h
 * --------------------
 * The header file of tools.cpp
 */
#ifndef TOOLS_H
#define TOOLS_H
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<ctime>
// #include<string.h>

using namespace std;

// Function prototypes
/*
 * Function: strip
 * Usage: str = strip(string);
 * -----------------------------------------------------
 * Delete spaces and tabs at the beginning and the end of a string
 */
/*
string strip(string &str);
*/
string strip(string str);

int getindex(string element, string array[], int length);

bool file_exist(string filename);

vector<string> process_path(string raw);

string slash_trans(string raw);

string add_placeholder(string raw, int length);

string add_placeholder(int raw, int length);

string chartostring(char* raw, int size);

bool all_placeholder(string raw);

int get_cur_time();

#endif // TOOLS_H

