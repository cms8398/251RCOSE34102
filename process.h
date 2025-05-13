#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESSES 10

//프로세스 상태 열거형형
typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

//process의 구조체 선언
typedef struct {
    int pid; // Process ID
    int priority; // Process priority
    int CPU_burst; // CPU time used
    int arrival_time; // Arrival time
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    ProcessState state; // Process state
}Process;

void print_process(Process* process);
Process * create_process(int num);
void process_init(Process* new_process, int index);
void delete_processes(Process* processes);


//stdlib.h의 qsort를 사용하기 위한 compare function들
int compare_process_by_arrival(const void *a, const void *b); 
int compare_process_by_CPU_burst(const void *a, const void *b);


#endif // 