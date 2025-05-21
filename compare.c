#include "process.h"
#include "compare.h"


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
    if (p1->CPU_burst == p2->CPU_burst)
    {
        return (p1->arrival_time - p2->arrival_time); //tie breaking 기준 추가
    }
    return (p1->CPU_burst - p2->CPU_burst);
}

//compare function for qsort, priority를 기준으로 process들을 오름차순 정렬을 사용.
int compare_process_by_priority(const void *a, const void *b)
{
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    if (p1->priority == p2->priority)
    {
        return (p1->arrival_time - p2->arrival_time); //tie breaking 기준 추가
    }
    return (p1->priority - p2->priority);
}

//compare function for qsort, start time을 기준으로 process들을 오름차순 정렬을 사용. 간트차트 출력을 위해 사용
int compare_process_by_start_time(const void *a, const void *b)
{
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return (p1->start_time - p2->start_time);
}


int compare_process_by_remaining_time(const void *a, const void *b)
{
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    if (p1->remaining_time == p2->remaining_time)
    {
        return (p1->arrival_time - p2->arrival_time); //tie breaking 기준 추가
    }
    return (p1->remaining_time - p2->remaining_time);
}


