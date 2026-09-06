#include "graph.h"
#include <stdlib.h>

Graph* graph_create(int vertices) {
    if (vertices <= 0) return NULL;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) return NULL;
    graph->vertices = vertices;
    graph->edge_count = 0;
    graph->adjacency_lists = (Edge**)calloc(vertices, sizeof(Edge*));
    if (graph->adjacency_lists == NULL) {
        free(graph);
        return NULL;
    }
    return graph;
}

void graph_free(Graph* graph) {
    if (graph == NULL) return;
    for (int i = 0; i < graph->vertices; i++) {
        Edge* current = graph->adjacency_lists[i];
        while (current != NULL) {
            Edge* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjacency_lists);
    free(graph);
}

int graph_is_valid_vertex(const Graph* graph, int vertex) {
    return graph != NULL && vertex >= 0 && vertex < graph->vertices;
}

int graph_add_edge(Graph* graph, int source, int destination, int weight) {
    if (!graph_is_valid_vertex(graph, source) || !graph_is_valid_vertex(graph, destination) || weight <= 0) return 0;
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    if (new_edge == NULL) return 0;
    new_edge->destination = destination;
    new_edge->weight = weight;
    new_edge->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_edge;
    graph->edge_count++;
    return 1;
}

int graph_add_undirected_edge(Graph* graph, int a, int b, int weight) {
    int first = graph_add_edge(graph, a, b, weight);
    int second = graph_add_edge(graph, b, a, weight);
    return first && second;
}
