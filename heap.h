//sjf scheduling algorithm을 위한 힙을 구현한 헤더파일.
// heap.h
#ifndef HEAP_H
#define HEAP_H

#include "process.h"

#define MAX_HEAP_SIZE 100

typedef struct {
    Process* data[MAX_HEAP_SIZE]; // 포인터 배열
    int size;
} MinHeap;

void init_heap(MinHeap* h);
void insert_heap(MinHeap* h, Process* p);
Process* extract_min(MinHeap* h);
int is_empty(MinHeap* h);

#endif // HEAP_H
