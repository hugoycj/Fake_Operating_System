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
#include "Process.h"

#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

class ProcessControlBlock
{
public:
    ProcessControlBlock(int cur_id, string name, int runtime, Process *p)
    {
        process_id = cur_id;
        process_name = name;
        process_state = 'W';
        process_run_time = runtime;
        process_arrive_time = time(&process_arrive_time);
        process_link = p;
        process_end_time = -1;
        process_priority = 999;
    }

	int process_id; ///< Process unique ID
    string process_name; ///< The same as the program name, which might be the same as the other process
    char process_state; ///< "W", "R", "F"
    time_t process_arrive_time; ///< the process preparing finished time
    int process_run_time; ///< how much time the process cost
    time_t process_end_time; ///< time when process end to run
    float process_priority; ///< priority
    Process *process_link; ///< link to process

    int get_id()
    {
        return process_id;
    }
private:
};

#endif // PROCESS_CONTROL_BLOCK_H
