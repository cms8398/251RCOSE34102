#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include "process.h"
//원형 큐로 구현하는 ready queue
typedef struct {
    Process** data;     // 포인터 배열 (동적 할당)
    int capacity;
    int front;
    int rear;
    int size;
} ReadyQueue;

ReadyQueue* create_queue(int capacity);
void destroy_queue(ReadyQueue* q);

int is_queue_empty(ReadyQueue* q);
int is_full(ReadyQueue* q);
void enqueue(ReadyQueue* q, Process* p);
Process* dequeue(ReadyQueue* q);
void increment_waiting_times(ReadyQueue* q);

#endif