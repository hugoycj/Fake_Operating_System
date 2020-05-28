/*
 * File: CLI.h
 * --------------------
 * The Command Line Interface's Header File
 */

#ifndef CLI_H
#define CLI_H
#include "fs.h"

using namespace std;


// constants
// const string app_name;

// Function prototypes

// Shell functions
/*
// read
void do_read(FileSystem &fs, vector<string> parameters, vector<int> locations);

// write
void do_write(FileSystem &fs, vector<string> parameters, vector<int> locations);
*/

// delete
void do_delete(FileSystem &fs, vector<string> parameters, vector<int> locations);

// help
void do_help(FileSystem &fs, vector<string> parameters, vector<int> locations);

// copyin
void do_copyin(FileSystem &fs, vector<string> parameters, vector<int> locations);

// copyout
void do_copyout(FileSystem &fs, vector<string> parameters, vector<int> locations);

// copybetween
void do_copybetween(FileSystem &fs, vector<string> parameters, vector<int> locations);

// mount
void do_mount(FileSystem &fs, vector<string> parameters, vector<int> locations);

// unmount
void do_unmount(FileSystem &fs, vector<string> parameters, vector<int> locations);

// dir
void do_dir(FileSystem &fs, vector<string> parameters, vector<int> locations);

// make directory
void do_md(FileSystem &fs, vector<string> parameters, vector<int> locations);

// remove directory
void do_rd(FileSystem &fs, vector<string> parameters, vector<int> locations);

// change directory
void do_cd(FileSystem &fs, vector<string> parameters, vector<int> locations);

// copy
void do_copy(FileSystem &fs, vector<string> parameters, vector<int> locations);

// move
void do_move(FileSystem &fs, vector<string> parameters, vector<int> locations);

// rename
void do_rename(FileSystem &fs, vector<string> parameters, vector<int> locations);

// version
void do_version(FileSystem &fs, vector<string> parameters, vector<int> locations);

// check disk
void do_chkdsk(FileSystem &fs, vector<string> parameters, vector<int> locations);

// format
void do_format(FileSystem &fs, vector<string> parameters, vector<int> locations);

// get attribute
void do_getattr(FileSystem &fs, vector<string> parameters, vector<int> locations);

// set attribute
void do_setattr(FileSystem &fs, vector<string> parameters, vector<int> locations);

// open
void do_open(FileSystem &fs, vector<string> parameters, vector<int> locations);

// create
void do_create(FileSystem &fs, vector<string> parameters, vector<int> locations);



/*
 * Function: Command Line Interface
 * Usage: CommandLineInterface();
 * -----------------------------------------------------
 * boost the Command Line Interface Module
 */
void CommandLineInterface();

/*
 * Function: extract_part
 * Usage: vector<string> part = extract_part(line, seperator)
 * -----------------------------------------------------
 * Store each part of the string (seperated by seperator) in a vector
 */
vector<string> extract_part(string line, string seperator);

/*
 * Function: locate_parameter
 * Usage: vector<int> loaction = locate_parameter(parameters);
 * -------------------------------
 * Return the parameter(with "-")'s location
 */
vector<int> locate_parameter(vector<string> parameters);

/*
 * Function: process_instruction
 * Usage: process_instruction(line);
 * -------------------------------
 * Process the instructions 
 */
void process_instruction(FileSystem &fs, string line);

/*
 * Function: process_line
 * Usage: process_line(line);
 * -------------------------------
 * Process the lines
 */
void process_line(FileSystem &fs, string line);

/*
 * Function: execute_instruction
 * Usage: execute_instruction(parameters, locations);
 * ---------------
 * Identify each instruction and link them to their funcions
 */
void execute_instruction(FileSystem &fs, vector<string> parameters, vector<int> locations);

#endif // CLI_H
