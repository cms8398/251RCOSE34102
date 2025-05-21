#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "compare.h"

void simple_gantt(Process* processes, int num_processes) //간트 차트 출력 -> fcfs, sjf 함수 호출 후 사용할 함수
{
    //processes 배열을 현재 arrival_time이 빠른 순서대로 정렬함.
    //해당 순서대로 각 프로세스의 start time과 completion time 저장.
    qsort(processes, num_processes, sizeof(Process), compare_process_by_start_time);
    int start_times[num_processes];
    int completion_times[num_processes];

    for(int i = 0; i < num_processes; i++)
    {
        start_times[i] = processes[i].start_time;
        completion_times[i] = processes[i].completion_time;
    }
    
    //간트차트 -> 문자열 형태로 작성
    char chart[1000] = {0}; // 간트 차트의 길이를 1000으로 설정, '__'가 1 unit time을 나타냄
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
    printf("Gantt Chart of scheduled processes!\n");
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

void new_gantt(int* log) {
    int i = 0;

    // 1. 프로세스 라인: 각 구간에 | Pn | 형식으로 출력
    while (log[i] != -2) {
        if(log[i] == -1){
          printf("| IDLE");
          i++;
        }
        else
        {
          printf("| P%-2d ", log[i]);
          i++;
        }
    }

    printf("|\n");

    // 2. 아래 시간 라인: 구간 시작점 ~ 마지막
    for (int j = 0; j <= i; j++) {
        printf("%-6d", j);
    }
    printf("\n");
}

