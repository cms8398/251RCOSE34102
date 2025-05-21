#include "ready_queue.h"
#include <stdlib.h>
#include <stdio.h>

ReadyQueue* create_queue(int capacity) {
    ReadyQueue* q = malloc(sizeof(ReadyQueue));
    if (!q) {
        fprintf(stderr, "Queue allocation failed\n");
        exit(EXIT_FAILURE);
    }

    q->data = malloc(sizeof(Process*) * capacity);
    if (!q->data) {
        fprintf(stderr, "Queue internal array allocation failed\n");
        free(q);
        exit(EXIT_FAILURE);
    }

    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    return q;
}

void destroy_queue(ReadyQueue* q) {
    if (q) {
        free(q->data);
        free(q);
    }
}

int is_queue_empty(ReadyQueue* q) {
    return q->size == 0;
}

int is_full(ReadyQueue* q) {
    return q->size == q->capacity;
}

void enqueue(ReadyQueue* q, Process* p) {
    if (is_full(q)) {
        fprintf(stderr, "Ready queue overflow!\n");
        return;
    }
    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % (q->capacity);
    q->size++;
}

Process* dequeue(ReadyQueue* q) {
    if (is_queue_empty(q)) {
        fprintf(stderr, "Ready queue underflow!\n");
        return NULL;
    }
    Process* p = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

void increment_waiting_times(ReadyQueue* q) {
    for (int i = 0; i < q->size; i++) {
        Process* p = q->data[(q->front + i) % q->capacity];
        p->waiting_time++;
    }
}