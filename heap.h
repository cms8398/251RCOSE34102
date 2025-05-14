//sjf scheduling algorithm을 위한 힙을 구현한 헤더파일.
// heap.h
#ifndef HEAP_H
#define HEAP_H

#include "process.h"
#include "scheduler_type.h"

typedef struct {
    Process** data; // 포인터 배열
    int size;
    int capacity;
} MinHeap;

MinHeap* create_heap(int capacity);
void insert_heap(MinHeap* h, Process* p, SchedulerType type);
Process* extract_min(MinHeap* h, SchedulerType type);
int is_empty(MinHeap* h);
void destroy_heap(MinHeap* h);
void increment_heap_waiting_times(MinHeap *h);

#endif // HEAP_H
