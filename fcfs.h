#ifndef FCFS_H
#define FCFS_H
#include "process.h"
#include <stdio.h>
#include <stdlib.h>

//fcfs 알고리즘을 구현한 함수
void fcfs(Process* processes, int num_processes);
void fcfs_gantt(Process* processes, int num_processes);

#endif // FCFS_H