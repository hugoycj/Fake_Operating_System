/**
 * @file ProcessesList.h
 * @brief 包含所有process的PCB，并可以输出响应比最高的PCB   
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
private:
    std::vector<ProcessControlBlock> Process_List;
    int size;
    int current_id;
    time_t start_time;
    time_t present_time;
};

#endif
