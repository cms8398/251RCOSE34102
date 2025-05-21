#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
#include "heap.h"
#include "schedulers.h"
#include "scheduler_type.h"
#include "compare.h"

void SJF(Process* processes, int num_processes) {
    
    SchedulerType type = sjf;
    // 프로세스 도착 시간에 따라 정렬
    qsort(processes, num_processes, sizeof(Process), compare_process_by_arrival);
    
    CPU cpu;

    MinHeap *rq =  create_heap(num_processes, compare_process_by_CPU_burst);
    create_cpu(&cpu);

    int completed = 0;
    int next = 0;
    
    printf("SJF Scheduling initiated...\n");

    while(completed < num_processes)
    { 
        while(next < num_processes && processes[next].arrival_time == cpu.time) //현재 시간에 도착한 프로세스들 힙에 삽입.
        {
            insert_heap(rq, &processes[next]);
            processes[next].state = READY;
            processes[next].waiting_time = 0;
            next++;
        }
        
        if(cpu_is_idle(&cpu) && !is_empty(rq)) //cpu가 idle하고 레디큐에 프로세스가 있다면
        {
            Process* p = extract_min(rq); //레디큐에서 프로세스를 꺼내서 cpu에 할당
            cpu_assign(&cpu, p);
        }

        increment_heap_waiting_times(rq); //레디큐(힙)에 있는 프로세스들의 waiting time 증가
        completed += cpu_tick(&cpu); //1 time unit 실행
    }

    destroy_heap(rq); //힙 메모리 해제
}

