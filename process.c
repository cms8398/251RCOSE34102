#include "process.h"
#include <stdio.h>
#include <stdlib.h>

void print_process(Process* process) {
    printf("-------------------------\n");
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

//process 초기화 함수.
void process_init(Process* new_process, int index) {
    //waiting_time, turnaround_time, completion_time, start time은 스케줄링 후에 업데이트되므로 -1로 초기화
    new_process->pid = index; // index를 pid로 사용
    new_process->priority = rand() % 10; // Set the priority between 0 and 9
    new_process->CPU_burst = rand() % 20 + 1; // Set the CPU burst time between 1 and 20
    new_process->arrival_time = rand() % 11; // Set the arrival time between 0 and 10
    new_process->remaining_time = new_process->CPU_burst; // remaining time은 CPU burst와 같음
    new_process->state = NEW; // 초기 상태는 NEW
    new_process->start_time = -1; // 시작 시간은 아직 정해지지 않음.
    new_process->completion_time = -1; // 완료 시간은 아직 정해지지 않음.
    new_process->waiting_time = -1; // 대기 시간은 아직 정해지지 않음.
    new_process->turnaround_time = -1; // 반환 시간은 아직 정해지지 않음.

    return;
}

//compare function for qsort, arrival time을 기준으로 process들을 오름차순 정렬을 사용. fcfs는 도착시간이 빠를수록 우선순위가 높으므로
int compare_process_by_arrival(const void *a, const void *b){
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return (p1->arrival_time - p2->arrival_time);
}

//compare function for qsort, CPU burst time을 기준으로 process들을 오름차순 정렬을 사용. sjf는 CPU burst가 짧을수록 우선순위가 높으므로
int compare_process_by_CPU_burst(const void *a, const void *b){
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return (p1->CPU_burst - p2->CPU_burst);
}

//process들에 할당한 메모리를 free해주는 함수
void delete_processes(Process* processes) {
    free(processes);
}
