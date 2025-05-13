//힙을 실제로 구현한 함수들
// heap.c
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void init_heap(MinHeap* h) {
    h->size = 0;
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
        if (h->data[parent]->CPU_burst > h->data[index]->CPU_burst) {
            swap(&h->data[parent], &h->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap* h, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < h->size && h->data[left]->CPU_burst < h->data[smallest]->CPU_burst)
            smallest = left;
        if (right < h->size && h->data[right]->CPU_burst < h->data[smallest]->CPU_burst)
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
    if (h->size >= MAX_HEAP_SIZE) {
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