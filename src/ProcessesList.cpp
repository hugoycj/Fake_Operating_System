/**
 * @file ProcessesList.cpp
 * @brief 包含所有process的PCB，并可以输出响应比最高的PCB   
 * member function of ProcessesList.h
 * @author Shiyi Zheng
 */

#include "ProcessesList.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

typedef ProcessControlBlock PCB;


ProcessesList::ProcessesList()
{
    size = 0;
    current_id = 1;
    char tmp[64];
    time(&start_time);
    printf("Global start time is:");
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&start_time));
    std::cout << tmp << std::endl;
    clean();
}
/**
 * @brief input is to input the informations of a process
 *
 * input has no parameter or return value
 */
void ProcessesList::input()
{
//    int i,num;
//    char ch;
//    std::cout << "\n请输入进程个数:";
//    scanf("%d", &num);
//    for(i=0;i<num;i++)
//    {
//        PCB pr= PCB();
//        char tmp[64];
////        printf("输入进程名:");
////        scanf("%s",pr.process_name);

//        printf("进程到达时间为");
//        time(&pr.process_arrive_time);
//        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&pr.process_arrive_time));
//        std::cout << tmp << std::endl;

//        printf("进程运行时间为");
//        scanf("%d",&pr.process_run_time);
//        while( (pr.process_arrive_time) < 0 )
//        {
//            while( (ch=getchar()) != '\n' && ch!=EOF);/*清除键盘输入缓冲区*/
//            printf("进程运行时间必须非负数，请重新输入:");
//            scanf("%d",&pr.process_arrive_time);
//        }
//        printf("\n");

//        pr.process_state='W'; //Wait等待标志
//        pr.process_id = current_id;
////        pr.process_link=NULL; //指向空指针
//        pr.process_end_time = -1; //-表示未结束
//        pr.process_priority = 0;//0代表最小，越大优先级越高
//        Process_List.push_back(pr);
//        size++;
//        current_id++;
//        calculate_Priority();
//        sort(); //调用sort函数
//    }
};

/**
 * @brief sort is a function to sort the processes by processes' priority
 *
 * sort has no return value, the parameter is a class tuple
 */
void ProcessesList::sort()
{   
    int i, j;
    if (size == 1)
        return;
    else
    {
        for (i = 0; i <= size; i++)
        {
            for (j = i+1; j <= size - 1; j++)
            {
                if (Process_List[i].process_priority > Process_List[j].process_priority)
                {
                    PCB temp = Process_List[j];
                    Process_List[j] = Process_List[i];
                    Process_List[j] = temp;
                }
            }
        }
     }

}

/**
*  @brief display is a function to display process and its properties
*
*  display has no return value, the parameter is a Pointer variable of process
*/
void ProcessesList::display()
{
    printf("\n|ID |Priority  |Name    |State  |Arrive Time |Run Time |Start Time |End Time |\n");
    if (isEmpty())
        return;
    else
    {
        for (int i=0; i < size; i++)
        {
            ProcessControlBlock pr = Process_List[i];
            show_single_pcb(pr);
         }
    }
}

void ProcessesList::show_single_pcb(ProcessControlBlock &pr)
{
    printf("|%d  ", pr.process_id);
    printf("|%f  ", pr.process_priority);
    printf("|%s\t", pr.process_name);
    printf("|%c\t", pr.process_state);
    printf("|%d\t", (int) difftime(present_time, pr.process_arrive_time));
    printf("|%d\t", pr.process_run_time);
//    printf("|%d\t", pr.process_start_time);
    printf("|%d\t", pr.process_end_time);
    printf("\n");
}

/**
*  @brief output is a fuction to set the state of process with biggest priority as "Run"
*
*  the parameter is a class tuple of PCB, no return value
*/
void ProcessesList::output()
{
    Process_List[0].process_state = (char) 'R';
/// Return PCB
}

/**
*  @brief clean is to enpty all element in process list
*
*  the parameter is a process list, return no value
*/
void ProcessesList::clean()
{
    Process_List.clear();
}

/**
 *  @brief calculate_priority can calculate all priority in process list
 *
 *  the parameter is a process list, return no value
 */
void ProcessesList::calculate_Priority()
{
    time(&present_time);
    for (int i = 0; i < size; i++)
    {
        PCB *pr;
        pr = &Process_List[i];
        pr->process_priority = difftime(present_time, pr->process_arrive_time) / pr->process_run_time + 1;
    }
}

bool ProcessesList::isEmpty()
{
       return (size == 0);
}
