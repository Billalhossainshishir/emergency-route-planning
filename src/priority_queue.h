#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct PriorityQueueNode {
    int vertex;
    int priority;
} PriorityQueueNode;

typedef struct PriorityQueue {
    PriorityQueueNode* items;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* priority_queue_create(int capacity);
void priority_queue_free(PriorityQueue* queue);
int priority_queue_is_empty(const PriorityQueue* queue);
int priority_queue_insert(PriorityQueue* queue, int vertex, int priority);
int priority_queue_extract_min(PriorityQueue* queue, int* vertex, int* priority);

#endif
