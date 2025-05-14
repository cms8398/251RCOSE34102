#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
#include "fcfs.h"
#include "ready_queue.h"

void fcfs(Process* processes, int num_processes) //fcfs 알고리즘
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

void simple_gantt(Process* processes, int num_processes) //간트 차트 출력 -> fcfs 함수 호출 후에 출력
{
    //processes 배열을 현재 arrival_time이 빠른 순서대로 정렬함.
    //해당 순서대로 각 프로세스의 start time과 completion time 저장.
    qsort(processes, num_processes, sizeof(Process), compare_process_by_arrival);
    int start_times[num_processes];
    int completion_times[num_processes];

    for(int i = 0; i < num_processes; i++)
    {
        start_times[i] = processes[i].start_time;
        completion_times[i] = processes[i].completion_time;
    }
    
    //간트차트 -> 문자열 형태로 작성
    char chart[500] = {'\0'}; // 간트 차트의 길이를 500으로 설정, '__'가 1 unit time을 나타냄
    int current = 0;
    int i=0;
    while(i < num_processes)
    {
      while(current < start_times[i])
      {
        chart[current*2] = '_';
        chart[current*2+1] = '_';
        current++;
      } 
      
      if (current == start_times[i])
      {
        if(chart[current*2] == '\0')
        {
          chart[current*2] = '|';
          chart[current*2+1] = '_';
        }
        current++;
      }
      
      while(current < completion_times[i])
      {
        chart[current*2] = '_';
        chart[current*2+1]= '_';
        current++;
      }
    
      if (current == completion_times[i])
      {
        i++;
        chart[current*2] = '|';

        if (i == num_processes)
        {
          break;
        }

        chart[current*2+1] = '_';
        current++;
      }
    }
    
    //실제 gannt chart display
    
    //첫번째 줄
    printf("Gantt Chart of FCFS\n");
    printf("--------------------------------\n");
    int *middle = (int*)malloc(sizeof(num_processes));
    
    for(int i=0; i<num_processes; i++)
    {
        middle[i] = (start_times[i] + completion_times[i]) / 2;
        printf("%d\n", middle[i]);
    }
    
    int j = 0;
    for(int i=0;i<num_processes;i++)
    {   
        while(j <= middle[i]-1)
        {
            j++;
            printf("  ");
        }
        printf("P%d",processes[i].pid);
        j++;
    }
    free(middle);
    printf("\n");

    // 두 번째 줄 간트 차트 출력
    printf("%s\n", chart);

    //마지막 줄 출력 -> process의 start, completion time 표시해주기  
    int count=0;
    i = 0;
    while(chart[count]!='\0')
    {
       if(chart[count*2]=='|')
       {
        printf("%d",count);
        if(count<10){
            printf(" ");
        }
       }
       else{
        printf("  ");
       }
       count++;
    }
    printf("\n");
}