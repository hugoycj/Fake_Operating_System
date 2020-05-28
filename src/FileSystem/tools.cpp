/*
 * File: tools.cpp
 * --------------------
 * Reusable Code Snippets
 */
#include "tools.h"

using namespace std;
/*
string strip(string &str){
    string new_str = str;

    // get rid of the white spaces
    new_str.erase(0,new_str.find_first_not_of(" "));
    new_str.erase(new_str.find_last_not_of(" ") + 1);

    // get rid of the tabs
    new_str.erase(0,new_str.find_first_not_of("\t"));
    new_str.erase(new_str.find_last_not_of("\t") + 1);

    return new_str;
};
*/
string strip(string str) {
	string new_str = str;

	// get rid of the white spaces
	new_str.erase(0, new_str.find_first_not_of(" "));
	new_str.erase(new_str.find_last_not_of(" ") + 1);

	// get rid of the tabs
	new_str.erase(0, new_str.find_first_not_of("\t"));
	new_str.erase(new_str.find_last_not_of("\t") + 1);

	return new_str;
};

int getindex(string element, string array[], int length) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (element == array[i]) {
            index = i;
            break;
		};
    };
    return index;
};

bool file_exist(string filename) {
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
};

vector<string> process_path(string raw) {
	// TODO: not comlete
	vector<string> path;
	return path;
};

string slash_trans(string raw) {
	// TODO: not complete
	return raw;
};

string add_placeholder(string raw, int length) {
	for (size_t i = raw.length(); i < length; i++) {
		raw = raw + ' ';
	};
	return raw;
};

string add_placeholder(int raw, int length) {
	string data = to_string(raw);
	return add_placeholder(data, length);
};

string chartostring(char* raw, int size) {
	string str;
	for (int i = 0; i < size; i++) {
		str = str + raw[i];
	};
	return str;
};

bool all_placeholder(string raw) {
	// not perfect
	if (raw.find_first_not_of(" ") != std::string::npos)
	{
		// TODO: verify whether the following is useful or not
		bool flag = true;
		for (int i = 0; i < raw.length(); i++) {
			if (raw[i] == '\0') {
				flag = false;
			};
			char one = raw[i];
		};
		if (!flag) {
			return true;
		}
		else {
			return false;
		};
		return false;
	}
	else {
		return true;
	};
};

int get_cur_time() {
	time_t t = std::time(0);
	return t;
};





