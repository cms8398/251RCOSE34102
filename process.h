#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid; // Process ID
    int priority; // Process priority
    int CPU_burst; // CPU time used
    int arrival_time; // Arrival time
}Process;

void print_process(Process* process);
Process * create_process(int num);
void process_init(Process* new_process);
void delete_processes(Process* processes);




#endif // 