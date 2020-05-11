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

typedef ProcessControlBlock PCB;


ProcessesList::ProcessesList()
{
    ProcessControlBlock Process_List[100];
}
/**
 * @brief input is to input the informations of a process
 *
 * input has no parameter or return value
 */
void ProcessesList::input()
{
    int i,num;
    char ch;
    //clrscr(); /*Windows清屏*/
    // system("clear");/*linux清屏函数*/
    printf("\n请输入进程个数:");
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        PCB pr= PCB();
        printf("输入进程名:");
        scanf("%s",pr.process_name);
        printf("输入进程到达时间:");
        scanf("%d",&pr.process_arrive_time);
        printf("输入进程需要运行时间:");
        scanf("%d",&pr.process_run_time);
        while( (pr.process_arrive_time) < 0 )
        {
            while( (ch=getchar()) != '\n' && ch!=EOF);/*清除键盘输入缓冲区*/
            printf("进程运行时间必须非负数，请重新输入:");
            scanf("%d",&pr.process_arrive_time);
        }
        printf("\n");
        pr.process_state='W'; //Wait等待标志
//        pr.process_link=NULL; //指向空指针
        pr.process_start_time = -999; //-999表示未开始
        pr.process_end_time = -999; //-999表示未开始
        pr.process_priority = 999;//999代表最小，1代表最大
        sort(); //调用sort函数
    }
};

/**
 * @brief sort is a function to sort the processes by processes' priority
 *
 * sort has no return value, the parameter is a class tuple
 */
void ProcessesList::sort()
{   
    int i, j;
    for (i  = 0; i  < 99; ++i)
    for (j  = 0; j  < 99; ++j)
    {
        if (Process_List[j].process_priority < Process_List[j + 1].process_priority)
        {
            float temp  = Process_List[j  + 1].process_priority;
            Process_List[j  + 1].process_priority = Process_List[j].process_priority;
            Process_List[j].process_priority = temp;
        }
    }
}

/**
*  @brief display is a function to display process and its properties
*
*  display has no return value, the parameter is a Pointer variable of process
*/
void ProcessesList::display(PCB *pr)
{
    printf("\n|Process ID |Process Name |Process State |Arrive Time |Run Time |Start Time |End Time |\n");
    printf("|%d\t", pr->process_id);
    printf("|%s\t", pr->process_name);
    printf("|%c\t", pr->process_state);
    printf("|%d\t", pr->process_arrive_time);
    printf("|%d\t", pr->process_run_time);
    printf("|%d\t", pr->process_start_time);
    printf("|%d\t", pr->process_end_time);
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
//    memset(Process_List, 0, sizeof(Process_List));
    Process_List = nullptr;
}

/**
 *  @brief calculate_priority can calculate all priority in process list
 *
 *  the parameter is a process list, return no value
 */
void ProcessesList::calculate_Priority()
{
    time_t present_time;
    int a = 0;
    present_time = time(NULL);
    while (a < 100)
    {
        if (Process_List[a].process_id)
        {
            Process_List[a].process_priority = (present_time - Process_List[a].process_arrive_time) / Process_List[a].process_run_time + 1;
        }
        else
        {
            break;
        }
        a++;
    }
}
