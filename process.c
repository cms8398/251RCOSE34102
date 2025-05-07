#include "process.h"
#include <stdio.h>
#include <stdlib.h>

void print_process(Process* process) {
    printf("--------------------------\n");
    printf("Process ID: %d\n", process->pid);
    printf("Priority: %d\n", process->priority);
    printf("CPU Burst: %d\n", process->CPU_burst);
    printf("Arrival Time: %d\n", process->arrival_time);
    printf("-------------------------\n\n");
}

Process * create_process(int num)
{
    Process *processes = (Process *)malloc(num * sizeof(Process));
    if (processes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    return processes;
}

void process_init(Process* new_process) {
    new_process->pid = rand() % 100; // Random PID betweebn 0 and 99
    new_process->priority = rand() % 10; // Set the priority between 0 and 9
    new_process->CPU_burst = rand() % 19 + 1; // Set the CPU burst time between 1 and 20
    new_process->arrival_time = rand() % 11; // Set the arrival time between 0 and 10
    return;
}

void delete_processes(Process* processes) {
    free(processes);
    processes = NULL;
}

