#include "cpu.h"
#include <stdio.h>

void cpu_init(CPU* cpu) {
    cpu->time = 0;
    cpu->current = NULL;
    cpu->clock = -1;
}

void cpu_assign(CPU* cpu, Process* p) {
    cpu->current = p;
    if (p->state == READY) {
        p->state = RUNNING;
        if (p->start_time == -1) {
            p->start_time = cpu->time;  // 만약 처음 할당받는거라면(process가 cpu를) -> process 자료구조에 시작시간을 기록해줘야함.
        }
    }
    cpu->clock = cpu->time; // 현재 시간을 시작 시간으로 설정
}

//이번 tick에서 프로세스가 종료된다면 1을 리턴, 그렇지 않으면 0을 반환함.
int cpu_tick(CPU* cpu) {
    //실행중인 프로세스가 있다면,
    if (cpu->current != NULL) {
        cpu->time++;
        cpu->current->remaining_time--;

        // 실행이 끝났다면 상태 업데이트
        if (cpu->current->remaining_time == 0) {
            cpu_finish(cpu);
            return 1; // 프로세스가 종료됨
        }
        return 0;
    }
    //실행 중인 프로세스가 없다면 cpu의 시간만 증가시키면 됨. 
    else {
        cpu->time++;
        return 0; 
    }
}

Process * cpu_release(CPU* cpu) //process가 cpu를 점유하다가 다른 process에게 cpu를 양도하는 경우
{
    if (cpu->current == NULL) return NULL;

    Process* p = cpu->current;
   
    p->state = READY;
    cpu->clock = -1; // 다음 프로세스가 할당될 때까지 -1로 초기화 
    cpu->current = NULL;
    return p; // cpu에서 해제된 프로세스 반환
}

void cpu_finish(CPU* cpu) {
    if (cpu->current == NULL) return;

    Process* p = cpu->current;
    p->completion_time = cpu->time;
    p->turnaround_time = p->completion_time - p->arrival_time;
    p->state = TERMINATED;
    cpu->clock = -1; // 다음 프로세스가 할당될 때까지 -1로 초기화
    cpu->current = NULL;
}

int cpu_is_idle(CPU* cpu) {
    return cpu->current == NULL;
}

int cpu_get_time(CPU* cpu) {
    return cpu->time;
}

Process* cpu_get_current(CPU *cpu)
{
    return cpu->current;
}