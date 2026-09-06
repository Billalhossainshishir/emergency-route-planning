#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

#define INF 999999

typedef struct DijkstraResult {
    int* distance;
    int* previous;
    int visited_count;
    int vertices;
} DijkstraResult;

typedef struct PathResult {
    int* path;
    int length;
    int total_cost;
} PathResult;

DijkstraResult* dijkstra_shortest_path(Graph* graph, int start_vertex);
void dijkstra_result_free(DijkstraResult* result);
PathResult* reconstruct_path(DijkstraResult* result, int destination);
void path_result_free(PathResult* path_result);
void print_shortest_path(DijkstraResult* result, int destination);

#endif
