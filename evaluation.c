#include <stdio.h>
#include <stdlib.h>
#include "process.h"

void print_average_performance(Process * processes, int num_processes)
{
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    
    printf("Average Waiting Time: %.2f\n", total_waiting_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / num_processes);
}

void print_each_performance(Process * processes, int num_processes)
{
    printf("----------------------------------------------------\n");
    printf("PID\tWaiting\tTurnaround\tStart\tCompletion\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%d\t%d\t\t%d\t%d\t%d\n", processes[i].pid, processes[i].waiting_time,
            processes[i].turnaround_time, processes[i].start_time, processes[i].completion_time);
    }
    printf("----------------------------------------------------\n\n");
}
    
