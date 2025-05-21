#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
#include "heap.h"
#include "schedulers.h"
#include "scheduler_type.h"

void pre_Priority(Process* processes, int num_processes, int *execution_log)
{
    SchedulerType type = priority;
    qsort(processes, num_processes, sizeof(Process), compare_process_by_arrival);
    CPU cpu;

    MinHeap *rq =  create_heap(num_processes,compare_process_by_priority);
    cpu_init(&cpu);

    int completed = 0;
    int next = 0;

    Process *released = NULL;
    Process *current_process = NULL;

    printf("preemptive Priority Scheduling initiated...\n");

    while(completed < num_processes)
    { 
        while(next < num_processes && processes[next].arrival_time == cpu.time) //현재 시간에 도착한 프로세스들 힙에 삽입.
        {
            insert_heap(rq, &processes[next]);
            processes[next].state = READY;
            processes[next].waiting_time = 0;
            next++;
        }
        
        if(!cpu_is_idle(&cpu) && !is_empty(rq)) //cpu가 idle하지 않고(검사해야할 프로세스가 있고), 레디큐에 프로세스가 있다면 -> 비교해봐야함
        {
            int result = compare_process_by_priority(cpu_get_current(&cpu), rq->data[0]);
            if(result > 0)
            {
                released = cpu_release(&cpu); //cpu를 해제(burst가 더 짧은 프로세스가 있으므로)
                insert_heap(rq, released); //레디큐에 다시 넣기
                released = NULL; //released는 NULL로 초기화
                //이제 cpu는 idle한 상태
            }
        }

        if(cpu_is_idle(&cpu) && !is_empty(rq)) //cpu가 idle하고 레디큐에 프로세스가 있다면
        {
            Process* p = extract_min(rq); //레디큐에서 프로세스를 꺼내서 cpu에 할당
            cpu_assign(&cpu, p);
        }

         //간트차트 출력용에 필요한 로그 기록을 위해 executed_pid를 기록
        current_process = cpu_get_current(&cpu);
        if(current_process == NULL)
        {
            execution_log[cpu.time] = -1; //간트차트 출력용 로그 기록 -> idle 상태일때는 -1로 기록
        }
        else
        {
            execution_log[cpu.time] = current_process->pid; //간트차트 출력용 로그 기록
        }

        increment_heap_waiting_times(rq); //레디큐(힙)에 있는 프로세스들의 waiting time 증가
        completed += cpu_tick(&cpu); //1 time unit 실행
    }
    execution_log[cpu.time] = -2; //간트차트 출력용 -> 출력이 끝나는 index의 값은 -2로 기록
    destroy_heap(rq); //힙 메모리 해제
}