/**
 * @file ProcessesList.h
 * @brief PCB that contains all process，can respond to PCB with the highest priority
 * 
 * @author Shiyi Zheng
 */

#ifndef PROCESSESLIST_H
#define PROCESSESLIST_H
#include "ProcessControlBlock.h"
#include <vector>

class ProcessesList
{
public:
    ProcessesList();
    void input();
    void sort();
    void display();
    ProcessControlBlock output();
    void clean();
    void calculate_Priority();
    bool isEmpty();
    void push(ProcessControlBlock pcb);
    int size_of_tuple(ProcessControlBlock Process_List[100]);
    void show_single_pcb(ProcessControlBlock &pr);
    int get_cur_id();
    std::vector<ProcessControlBlock> Process_List;
private:
    int size;
    int current_id;
    time_t start_time;
    time_t present_time;
};

#endif
