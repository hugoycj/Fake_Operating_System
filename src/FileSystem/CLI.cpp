/*
 * File: CLI.cpp
 * --------------------
 * The Command Line Interface
 */
#include "CLI.h"

using namespace std;

// constants
const string position_name = "";

// main function
/*
int main() {
    FileSystem fs;
    cout << "File System > File System Successfully Started" << endl;
    for (string line; cout << position_name << " > " && getline(cin, line); )
    {
        if (!line.empty())
        {
            if (line == "exit" || line == "quit") {
                cout << "You will exit the file system interface" << endl;
                break;
            }
            process_line(fs, line);
        }
    }
    return 0;
};
*/
// functions

vector<string> extract_part(string line, string seperator)
{
    size_t pos1, pos2;
    vector<string> parameters;
    pos2 = line.find(seperator);
    pos1 = 0;
    while(pos2 != string::npos)
    {
        parameters.push_back(line.substr(pos1, pos2-pos1));

        pos1 = pos2 + seperator.length();
        pos2 = line.find(seperator, pos1);
    }
    if(pos1 != line.length()){
        parameters.push_back(line.substr(pos1));
    }
    return parameters;
};

vector<int> locate_parameter(vector<string> parameters){
    vector<int> location;
    for(int i = 0; i < parameters.size(); i++) {
        if (&parameters[i][0] == "-") {
            location.push_back(i);
        };
    };
    return location;
};

void process_instruction(FileSystem &fs, string line) {
    vector<string> parameters = extract_part(line, " ");
    vector<int> locations = locate_parameter(parameters);
    execute_instruction(fs, parameters, locations);
};

void process_line(FileSystem &fs, string line) {
    vector<string> instructions = extract_part(line, "&&");
    for(size_t i = 0; i < instructions.size(); i++) {
		string temp = strip(instructions[i]);
        process_instruction(fs, temp);
    };
};

void execute_instruction(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	string Instructions[29] = {"dir", "md", "mkdir", "rd", "rmdir", "cd", "chdir", "copy", "cp", "del", "move", "mv", 
			"ren", "rename", "chkdsk", "setdsk", "ver", "version", "format", "getattr", "setattr", "open", "copyin", "copyout", "copybetween", 
			"mount", "unmount", "help", "create"};
    // string Parameters[] = {};
	// TODO: setdsk
    int index = getindex(parameters[0], Instructions, 29/*the length of the Instructions*/);
    if (index != -1) {
        if (parameters[0] == "dir") {
            do_dir(fs, parameters, locations);
        }
		else if (parameters[0] == "md" || parameters[0] == "mkdir") {
            do_md(fs, parameters, locations);
		}
		else if (parameters[0] == "rd" || parameters[0] == "rmdir") {
			do_rd(fs, parameters, locations);
		}
		else if (parameters[0] == "cd" || parameters[0] == "chdir") {
			do_cd(fs, parameters, locations);
        }
		else if (parameters[0] == "del") {
            do_delete(fs, parameters, locations);
        }
		else if (parameters[0] == "help") {
            do_help(fs, parameters, locations);
        }
		else if (parameters[0] == "copyin") {
            do_copyin(fs, parameters, locations);
        }
		else if (parameters[0] == "copyout") {
            do_copyout(fs, parameters, locations);
        }
		else if (parameters[0] == "copybetween") {
            do_copybetween(fs, parameters, locations);
        }
		else if (parameters[0] == "mount") {
            do_mount(fs, parameters, locations);
        }
		else if (parameters[0] == "unmount") {
            do_unmount(fs, parameters, locations);
        }
		else if (parameters[0] == "cp" || parameters[0] == "copy") {
			do_copy(fs, parameters, locations);
		}
		else if (parameters[0] == "mv" || parameters[0] == "move") {
			do_move(fs, parameters, locations);
		}
		else if (parameters[0] == "ren" || parameters[0] == "rename") {
			do_rename(fs, parameters, locations);
		}
		else if (parameters[0] == "ver" || parameters[0] == "version") {
			do_version(fs, parameters, locations);
		}
		else if (parameters[0] == "chkdsk") {
			do_chkdsk(fs, parameters, locations);
		}
		else if (parameters[0] == "format") {
			do_format(fs, parameters, locations);
		}
		else if (parameters[0] == "getattr") {
			do_getattr(fs, parameters, locations);
		}
		else if (parameters[0] == "setattr") {
			do_setattr(fs, parameters, locations);
		}
		else if (parameters[0] == "open") {
			do_open(fs, parameters, locations);
		}
		else if (parameters[0] == "creare") {
			do_create(fs, parameters, locations);
		};
    };
};
















// shell functions

// delete
void do_delete(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// help
void do_help(FileSystem &fs, vector<string> parameters, vector<int> locations) {
    if (parameters.size() == 1) {
        cout << "Usage: help [instruction you want to know]" << endl;
    };
};

// copyin
void do_copyin(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// copyout
void do_copyout(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// copybetween
void do_copybetween(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// mount
void do_mount(FileSystem &fs, vector<string> parameters, vector<int> locations) {
    // @parameter mount
    // @parameter drive letter
    // @parameter real path
    
    // TODO: Verification
    string path = parameters[1];
    string drive_letter = parameters[2];
    if (fs.mount(path, drive_letter)) {
        cout << "Disk mounted successfully" << endl;
    } else {
        cout << "Disk mounted fail" << endl;
    };
};

// unmount
void do_unmount(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	// TODO: check unmount reliability
    // @parameter unmount
    // @parameter drive letter

    // TODO: Verification
    string drive_letter = parameters[1];
    fs.unmount(drive_letter);
};

// dir
void do_dir(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	// TODO: different mode
	// TODO: problems in it
	vector<string> dir = fs.dir();
	for (size_t i = 0; i != dir.size(); i++) {
		int INodenum;
		string name;
		loadDirEntry(INodenum, name, dir[i]);
		cout << name << endl;
	};
};

// make directory
void do_md(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	if (!fs.md(parameters[1])) {
		cout << "make fail" << endl;
	};
};

// remove directory
void do_rd(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	if (!fs.rd(parameters[1])) {
		cout << "remove fail" << endl;
	};
};

// change directory
void do_cd(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	if (!fs.cd(parameters[1])) {
		cout << "no such directory" << endl;
	};
};

// copy
void do_copy(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// move
void do_move(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// rename
void do_rename(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// version
void do_version(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	cout << fs.ver << endl;
};

// check disk
void do_chkdsk(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// format
void do_format(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// get attribute
void do_getattr(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// set attribute
void do_setattr(FileSystem &fs, vector<string> parameters, vector<int> locations) {

};

// open
void do_open(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	string name;
	fs.open(name);
};

// create
void do_create(FileSystem &fs, vector<string> parameters, vector<int> locations) {
	string name;
	fs.create(name);
};



