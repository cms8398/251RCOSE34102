#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
#include "schedulers.h"
#include "ready_queue.h"

void FCFS(Process* processes, int num_processes) //fcfs 알고리즘
{
    qsort(processes, num_processes, sizeof(Process), compare_process_by_arrival);
    ReadyQueue* rq = create_queue(num_processes);
    
    CPU cpu;
    cpu_init(&cpu);
    
    int completed = 0; // 완료된 프로세스 수 -> while문 탈출조건임
    int next = 0; //processes배열에서 다음에 레디큐에 삽입될 프로세스의 인덱스
    
    printf("FCFS Scheduling initiated...\n");

    while(completed < num_processes)
    {
      while (next < num_processes && processes[next].arrival_time == cpu.time)
      {
        enqueue(rq, &processes[next]);
        processes[next].state = READY;
        processes[next].waiting_time = 0;
        next++;
      }

      if(cpu_is_idle(&cpu) && !is_queue_empty(rq)) //cpu가 idle하고 레디큐에 프로세스가 있다면
      {
        Process* p = dequeue(rq); //레디큐에서 프로세스를 꺼내서 cpu에 할당
        cpu_assign(&cpu, p);
      }

      increment_waiting_times(rq);
      completed += cpu_tick(&cpu); //1 time unit 실행

    }
}