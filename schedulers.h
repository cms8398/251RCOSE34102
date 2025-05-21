#ifndef SCHEDULERS_H
#define SCHEDULERS_H
#include "process.h"

 //사용할 스케줄러 알고리즘 함수 원형 선언
void FCFS(Process* processes, int num_processes);
void SJF(Process* processes, int num_processes);
void Priority(Process* processes, int num_processes);
void RR(Process *processes, int num_processes, int time_quantum, int* execution_log);
void pre_SJF(Process* processes, int num_processes, int *execution_log);
void pre_Priority(Process* processes, int num_processes, int *execution_log);

#endif