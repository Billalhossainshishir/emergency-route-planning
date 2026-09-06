#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "search.h"
#include "../tests/tests.h"

static void run_demo(void) {
    Graph* graph = graph_create(6);
    if (graph == NULL) return;

    graph_add_undirected_edge(graph, 0, 1, 4);
    graph_add_undirected_edge(graph, 0, 2, 2);
    graph_add_undirected_edge(graph, 1, 2, 1);
    graph_add_undirected_edge(graph, 1, 3, 5);
    graph_add_undirected_edge(graph, 2, 3, 8);
    graph_add_undirected_edge(graph, 3, 4, 2);
    graph_add_undirected_edge(graph, 4, 5, 3);

    DijkstraResult* result = dijkstra_shortest_path(graph, 0);
    if (result != NULL) {
        print_shortest_path(result, 5);
        dijkstra_result_free(result);
    }
    graph_free(graph);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--tests") == 0) {
        run_all_tests();
        return 0;
    }

    printf("Emergency Route Planning Demo\n");
    printf("=============================\n");
    run_demo();
    printf("\nRun with --tests to execute the test suite.\n");
    return 0;
}
