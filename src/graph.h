#ifndef GRAPH_H
#define GRAPH_H

typedef struct Edge {
    int destination;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Graph {
    int vertices;
    int edge_count;
    Edge** adjacency_lists;
} Graph;

Graph* graph_create(int vertices);
void graph_free(Graph* graph);
int graph_is_valid_vertex(const Graph* graph, int vertex);
int graph_add_edge(Graph* graph, int source, int destination, int weight);
int graph_add_undirected_edge(Graph* graph, int a, int b, int weight);

#endif
