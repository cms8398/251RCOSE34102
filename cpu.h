#ifndef CPU_H
#define CPU_H

#include "process.h"

typedef struct {
    int time;           // 현재 시간 (전역 시뮬레이션 시각)
    Process* current;   // 현재 실행 중인 프로세스
    int clock;     // 실행 중인 프로세스의 점유 시작 시간을 기록하는 변수 -> 새로운 프로세스의 실행 때마다 업데이트해야하고, 프로세스 점유 안할땐 -1
} CPU;

// 초기화
void cpu_init(CPU* cpu);

// 프로세스 할당
void cpu_assign(CPU* cpu, Process* p);

// 1 타임 유닛 실행 (1 tick)
int cpu_tick(CPU* cpu);

// 현재 프로세스 종료
void cpu_finish(CPU* cpu);

//현재 프로세스가 cpu 점유를 해제(종료된 건 아니고 roundrobin이나 preemptive scheduling을 위해서)
void cpu_release(CPU* cpu);

// 상태 확인
int cpu_is_idle(CPU* cpu);
int cpu_get_time(CPU* cpu);

#endif

