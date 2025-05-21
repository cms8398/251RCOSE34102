//힙을 실제로 구현한 함수들
#include <stdlib.h>
#include <stdio.h>
#include "process.h"
#include "heap.h"
#include "compare.h"

MinHeap* create_heap(int capacity, int (*compare)(const void*, const void*)) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        fprintf(stderr, "Heap allocation failed\n");
        exit(EXIT_FAILURE);
    }

    heap->size = 0;
    heap->capacity = capacity;
    heap->compare = compare;
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

void heapify_up(MinHeap* h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if(h->compare(h->data[parent], h->data[index]) > 0){
            swap(&h->data[parent], &h->data[index]);
            index = parent;
        } // 부모가 자식보다 작으면
        else{
            break;
        }
    }
}

void heapify_down(MinHeap* h, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if(left < h->size && h->compare(h->data[left], h->data[smallest]) < 0)
            smallest = left;
        if(right < h->size && h->compare(h->data[right], h->data[smallest]) < 0)
            smallest = right;
        
        if (smallest != index) {
            swap(&h->data[smallest], &h->data[index]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert_heap(MinHeap* h, Process* p) {
    if (h->size >= h->capacity) {
        fprintf(stderr, "Heap overflow\n");
        return;
    }
    h->data[h->size] = p;
    heapify_up(h, h->size);
    h->size++;
}

Process* extract_min(MinHeap* h) {
    if (is_empty(h)) {
        fprintf(stderr, "Heap underflow\n");
        exit(EXIT_FAILURE);
    }
    Process* min = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify_down(h, 0);
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
