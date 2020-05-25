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

// TODO: 补充对象注释
/*
 * @brief  class简要说明
 *
 * class详细说明。
 */
class ProcessesList
{
public:
    ProcessesList();
	void input(); /* 进程控制块插入函数*/	
    void sort();  /* 对进程进行优先级排列函数*/
    void display(); /*显示当前所有等待进程*/
	void output(); /*找到优先级第一或最高响应比的等待进程，并将其状态设置为“R”*/
	void clean(); /*清空所有进程*/
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
