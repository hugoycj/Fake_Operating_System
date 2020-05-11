#ifndef PROCESS_H
#define PROCESS_H
#include <string>

//TODO(hugoycj): change into address
class Process
{
public:
	Process();

	/**
	 * A function giving the ID of the process
	 * @return ID of the process
	 */
	int getID();

private:
	int id; 
	std::string text; ///< Program code
	std::string temp_data; ///< preload data from the file system or operating system
	std::string temp_heap; ///< heap to store some dynamic data during the execution of the program
	std::string temp_stack; ///< stack to store registers and some global variables
};


#endif // PROCESS_H
