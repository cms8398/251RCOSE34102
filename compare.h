#ifndef COMPARE_H
#define COMPARE_H
#include "process.h"
//qsort랑 힙에서 사용하기 위한 compare fucntion들
int compare_process_by_arrival(const void *a, const void *b); 
int compare_process_by_CPU_burst(const void *a, const void *b);
int compare_process_by_priority(const void *a, const void *b);
int compare_process_by_start_time(const void *a, const void *b);
int compare_process_by_remaining_time(const void *a, const void *b);
#endif