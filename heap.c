//힙을 실제로 구현한 함수들
// heap.c
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        fprintf(stderr, "Heap allocation failed\n");
        exit(EXIT_FAILURE);
    }

    heap->size = 0;
    heap->capacity = capacity;
    heap->data = (Process**)malloc(capacity * sizeof(Process*));
     if(heap->data ==NULL){
        fprintf(stderr, "Heap data allocation failed\n");
        exit(EXIT_FAILURE);
     }
    return heap;
}

int is_empty(MinHeap* h) {
    return h->size == 0;
}

void swap(Process** a, Process** b) {
    Process* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* h, int index, SchedulerType type) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (type == sjf) { // SJF
            if (h->data[parent]->CPU_burst > h->data[index]->CPU_burst) {
                swap(&h->data[parent], &h->data[index]);
                index = parent;
            } else {
                break;
            }
        } else if (type == priority) { // Priority
            if (h->data[parent]->priority > h->data[index]->priority) {
                swap(&h->data[parent], &h->data[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
}

void heapify_down(MinHeap* h, int index, SchedulerType type) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (type == sjf) {
            if (left < h->size && h->data[left]->CPU_burst < h->data[smallest]->CPU_burst)
                smallest = left;
            if (right < h->size && h->data[right]->CPU_burst < h->data[smallest]->CPU_burst)
                smallest = right;
        } else if (type == priority) {
            if (left < h->size && h->data[left]->priority < h->data[smallest]->priority)
                smallest = left;
            if (right < h->size && h->data[right]->priority < h->data[smallest]->priority)
                smallest = right;
        }

        if (smallest != index) {
            swap(&h->data[smallest], &h->data[index]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert_heap(MinHeap* h, Process* p, SchedulerType type) {
    if (h->size >= h->capacity) {
        fprintf(stderr, "Heap overflow\n");
        return;
    }
    h->data[h->size] = p;
    heapify_up(h, h->size,type);
    h->size++;
}

Process* extract_min(MinHeap* h, SchedulerType type) {
    if (is_empty(h)) {
        fprintf(stderr, "Heap underflow\n");
        exit(EXIT_FAILURE);
    }
    Process* min = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify_down(h, 0, type);
    return min;
}

void destroy_heap(MinHeap* h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

void increment_heap_waiting_times(MinHeap *h) 
{
    for(int i = 0; i< h->size; i++)
    {
        h->data[i]->waiting_time++;
    }
}
