#include "search.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

DijkstraResult* dijkstra_shortest_path(Graph* graph, int start_vertex) {
    if (graph == NULL || !graph_is_valid_vertex(graph, start_vertex)) return NULL;

    DijkstraResult* result = (DijkstraResult*)malloc(sizeof(DijkstraResult));
    if (result == NULL) return NULL;

    result->vertices = graph->vertices;
    result->visited_count = 0;
    result->distance = (int*)malloc(sizeof(int) * graph->vertices);
    result->previous = (int*)malloc(sizeof(int) * graph->vertices);
    if (result->distance == NULL || result->previous == NULL) {
        free(result->distance);
        free(result->previous);
        free(result);
        return NULL;
    }

    int* visited = (int*)calloc(graph->vertices, sizeof(int));
    if (visited == NULL) {
        free(result->distance);
        free(result->previous);
        free(result);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++) {
        result->distance[i] = INF;
        result->previous[i] = -1;
    }
    result->distance[start_vertex] = 0;

    PriorityQueue* queue = priority_queue_create(graph->vertices * graph->vertices);
    if (queue == NULL) {
        free(visited);
        free(result->distance);
        free(result->previous);
        free(result);
        return NULL;
    }

    priority_queue_insert(queue, start_vertex, 0);

    while (!priority_queue_is_empty(queue)) {
        int current_vertex;
        int current_distance;
        if (!priority_queue_extract_min(queue, &current_vertex, &current_distance)) break;
        if (!graph_is_valid_vertex(graph, current_vertex) || visited[current_vertex]) continue;

        visited[current_vertex] = 1;
        result->visited_count++;

        Edge* edge = graph->adjacency_lists[current_vertex];
        while (edge != NULL) {
            int neighbour = edge->destination;
            int new_distance = result->distance[current_vertex] + edge->weight;
            if (!visited[neighbour] && new_distance < result->distance[neighbour]) {
                result->distance[neighbour] = new_distance;
                result->previous[neighbour] = current_vertex;
                priority_queue_insert(queue, neighbour, new_distance);
            }
            edge = edge->next;
        }
    }

    priority_queue_free(queue);
    free(visited);
    return result;
}

PathResult* reconstruct_path(DijkstraResult* result, int destination) {
    if (result == NULL || destination < 0 || destination >= result->vertices) return NULL;
    if (result->distance[destination] == INF) return NULL;

    PathResult* path_result = (PathResult*)malloc(sizeof(PathResult));
    if (path_result == NULL) return NULL;

    path_result->path = (int*)malloc(sizeof(int) * result->vertices);
    if (path_result->path == NULL) {
        free(path_result);
        return NULL;
    }
    path_result->length = 0;
    path_result->total_cost = result->distance[destination];

    int current = destination;
    while (current != -1 && path_result->length < result->vertices) {
        path_result->path[path_result->length++] = current;
        current = result->previous[current];
    }

    for (int i = 0; i < path_result->length / 2; i++) {
        int temp = path_result->path[i];
        path_result->path[i] = path_result->path[path_result->length - 1 - i];
        path_result->path[path_result->length - 1 - i] = temp;
    }
    return path_result;
}

void path_result_free(PathResult* path_result) {
    if (path_result == NULL) return;
    free(path_result->path);
    free(path_result);
}

void dijkstra_result_free(DijkstraResult* result) {
    if (result == NULL) return;
    free(result->distance);
    free(result->previous);
    free(result);
}

void print_shortest_path(DijkstraResult* result, int destination) {
    PathResult* path_result = reconstruct_path(result, destination);
    if (path_result == NULL) {
        printf("No safe path available to vertex %d.\n", destination);
        return;
    }
    printf("Shortest distance to vertex %d is %d\n", destination, path_result->total_cost);
    printf("Path: ");
    for (int i = 0; i < path_result->length; i++) {
        printf("%d%s", path_result->path[i], i < path_result->length - 1 ? " -> " : "\n");
    }
    path_result_free(path_result);
}
