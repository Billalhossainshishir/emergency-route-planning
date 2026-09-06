#include "priority_queue.h"
#include <stdlib.h>

static void swap_nodes(PriorityQueueNode* a, PriorityQueueNode* b) {
    PriorityQueueNode temp = *a;
    *a = *b;
    *b = temp;
}

PriorityQueue* priority_queue_create(int capacity) {
    if (capacity <= 0) return NULL;
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (queue == NULL) return NULL;
    queue->items = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode) * capacity);
    if (queue->items == NULL) {
        free(queue);
        return NULL;
    }
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void priority_queue_free(PriorityQueue* queue) {
    if (queue == NULL) return;
    free(queue->items);
    free(queue);
}

int priority_queue_is_empty(const PriorityQueue* queue) {
    return queue == NULL || queue->size == 0;
}

int priority_queue_insert(PriorityQueue* queue, int vertex, int priority) {
    if (queue == NULL || queue->size >= queue->capacity) return 0;
    int index = queue->size;
    queue->items[index].vertex = vertex;
    queue->items[index].priority = priority;
    queue->size++;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (queue->items[parent].priority <= queue->items[index].priority) break;
        swap_nodes(&queue->items[parent], &queue->items[index]);
        index = parent;
    }
    return 1;
}

int priority_queue_extract_min(PriorityQueue* queue, int* vertex, int* priority) {
    if (queue == NULL || queue->size == 0) return 0;
    if (vertex != NULL) *vertex = queue->items[0].vertex;
    if (priority != NULL) *priority = queue->items[0].priority;

    queue->items[0] = queue->items[queue->size - 1];
    queue->size--;

    int index = 0;
    while (1) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;
        if (left < queue->size && queue->items[left].priority < queue->items[smallest].priority) smallest = left;
        if (right < queue->size && queue->items[right].priority < queue->items[smallest].priority) smallest = right;
        if (smallest == index) break;
        swap_nodes(&queue->items[index], &queue->items[smallest]);
        index = smallest;
    }
    return 1;
}
