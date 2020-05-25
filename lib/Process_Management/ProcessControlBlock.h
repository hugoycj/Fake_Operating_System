    /**
 * @file ProcessControlBlock.h
 * @brief show the state of the process.
 *
 * It includes following parts: 
 * Process ID (Process unique ID)，
 * Process name (The same as the program name, which might be the same as the other process)          
 * Process state (such as waiting, running or finished)
 * Arrive time (The process preparing finished time)
 * Run time (How much time the process cost)
 * Start time (time when process start to run)
 * End Time (time when process end to run)
 * Priority (the priority of processes)
 * 
 * @author Shiyi Zheng
 */

#include <string> 
#include <time.h>
//#include "Process.h"

#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H


class ProcessControlBlock
{
public:
    ProcessControlBlock()
    {
        process_id = -1;
        process_name[10] = 'null';
        process_state = '\0';
//        process_link=NULL; //指向空指针
        process_end_time = -1; //-1表示未开始
        process_priority = 999;//999代表最小，1代表最大
    }

	int process_id; ///< Process unique ID
	char process_name[10]; ///< The same as the program name, which might be the same as the other process
    char process_state; ///< "W", "R", "F"
    time_t process_arrive_time; ///< the process preparing finished time
    int process_run_time; ///< how much time the process cost
    time_t process_end_time; ///< time when process end to run
    float process_priority; ///< priority
//	Process *process_link; ///< link to process
	
private:
};

#endif // PROCESS_CONTROL_BLOCK_H