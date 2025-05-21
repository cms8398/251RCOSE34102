#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
#include "ready_queue.h"
#include "scheduler_type.h"
#include "schedulers.h"
#include "compare.h"

void RR(Process *processes, int num_processes, int time_quantum, int* execution_log)
{
  printf("Round_Robin Scheduling initiated...\n");
  
  qsort(processes, num_processes, sizeof(Process), compare_process_by_arrival);
    ReadyQueue* rq = create_queue(num_processes);
    
    CPU cpu;
    create_cpu(&cpu);
    
    int completed = 0; // 완료된 프로세스 수 -> while문 탈출조건임
    int next = 0; //processes배열에서 다음에 레디큐에 삽입될 프로세스의 인덱스
    int result = 0; // cpu_tick의 리턴값을 저장하는 변수
                    //time quantum만큼 실행했을때 preempt하거나 아니면 그냥 그대로 실행하던가, 아니면 실행이 끝나서 새로 할당해야하는 경우 구별
    Process* current_process = NULL;
    Process* released = NULL; //cpu를 점유하고 있는 프로세스가 time quantum만큼 실행했을때 cpu를 release 해주기 위해서 사용

    while(completed < num_processes)
    {
      //해당 시간에 도착한 프로세스들 레디큐에 삽입
      while (next < num_processes && processes[next].arrival_time == cpu.time)
      {
        enqueue(rq, &processes[next]);
        processes[next].state = READY;
        processes[next].waiting_time = 0;
        next++;
      }

      if(released != NULL) //cpu를 점유하고 있는 프로세스가 time quantum만큼 실행했을때 release 해준 프로세스 enqueue 해주기. 
      {
        enqueue(rq, released); //레디큐에 다시 넣기
        released = NULL; //released는 NULL로 초기화
      }

      if(cpu_is_idle(&cpu) && !is_queue_empty(rq)) //cpu가 idle하고 레디큐에 프로세스가 있다면
      {
        Process* p = dequeue(rq); //레디큐에서 프로세스를 꺼내서 cpu에 할당
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
      
      result = cpu_tick(&cpu); //1 time unit 실행
      increment_waiting_times(rq); //레디큐 존재하는 프로세스들 waiting time 증가시키기
      
      if (result == 1) //프로세스가 종료되는 경우
      {
        completed+=result;
      }
      else if(result ==0) 
      {
        if(cpu.clock != -1 && (cpu.time - cpu.clock) == time_quantum) //프로세스가 종료되지 않고(remaining time이 남고) + time_quantum이 소진된 경우
        {
            released = cpu_release(&cpu); //cpu를 점유하고 있는 프로세스가 time quantum만큼 실행했을때 cpu를 release 해주기
        }
      }
    }
    execution_log[cpu.time] = -2; //간트차트 출력용 -> 출력이 끝나는 index의 값은 -2로 기록
    destroy_queue(rq); //레디큐 메모리 해제
}