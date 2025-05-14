#ifndef FCFS_H
#define FCFS_H
#include "process.h"

//fcfs 알고리즘을 구현한 함수
void fcfs(Process* processes, int num_processes);
void simple_gantt(Process* processes, int num_processes);

#endif // FCFS_H