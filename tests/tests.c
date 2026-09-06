#include <stdio.h>
#include "tests.h"
#include "../src/graph.h"
#include "../src/priority_queue.h"
#include "../src/search.h"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

static void print_test_result(const char* test_name, int passed) {
    total_tests++;
    if (passed) {
        passed_tests++;
        printf("[PASS] %s\n", test_name);
    } else {
        failed_tests++;
        printf("[FAIL] %s\n", test_name);
    }
}

void run_graph_tests(void) {
    Graph* graph = graph_create(5);
    print_test_result("Graph can be created", graph != NULL);
    if (graph == NULL) return;
    print_test_result("Graph vertex count is correct", graph->vertices == 5);
    print_test_result("Valid edge is accepted", graph_add_edge(graph, 0, 1, 10) == 1);
    print_test_result("Invalid source vertex is rejected", graph_add_edge(graph, -1, 2, 10) == 0);
    print_test_result("Negative edge weight is rejected", graph_add_edge(graph, 1, 2, -5) == 0);
    graph_free(graph);
}

void run_priority_queue_tests(void) {
    PriorityQueue* queue = priority_queue_create(10);
    print_test_result("Priority queue can be created", queue != NULL);
    if (queue == NULL) return;
    print_test_result("Priority queue starts empty", priority_queue_is_empty(queue) == 1);
    priority_queue_insert(queue, 0, 20);
    priority_queue_insert(queue, 1, 10);
    priority_queue_insert(queue, 2, 30);
    priority_queue_insert(queue, 3, 5);
    print_test_result("Priority queue size is correct after inserts", queue->size == 4);
    int vertex, priority;
    priority_queue_extract_min(queue, &vertex, &priority);
    print_test_result("Priority queue extracts smallest priority first", vertex == 3 && priority == 5);
    priority_queue_extract_min(queue, &vertex, &priority);
    print_test_result("Priority queue extracts next smallest priority", vertex == 1 && priority == 10);
    priority_queue_free(queue);
}

void run_dijkstra_tests(void) {
    Graph* graph = graph_create(6);
    print_test_result("Dijkstra test graph can be created", graph != NULL);
    if (graph == NULL) return;
    graph_add_undirected_edge(graph, 0, 1, 4);
    graph_add_undirected_edge(graph, 0, 2, 2);
    graph_add_undirected_edge(graph, 1, 2, 1);
    graph_add_undirected_edge(graph, 1, 3, 5);
    graph_add_undirected_edge(graph, 2, 3, 8);
    graph_add_undirected_edge(graph, 2, 4, 10);
    graph_add_undirected_edge(graph, 3, 4, 2);
    graph_add_undirected_edge(graph, 3, 5, 6);
    graph_add_undirected_edge(graph, 4, 5, 3);
    DijkstraResult* result = dijkstra_shortest_path(graph, 0);
    print_test_result("Dijkstra result is created", result != NULL);
    if (result != NULL) {
        print_test_result("Start vertex distance is zero", result->distance[0] == 0);
        print_test_result("Shortest distance to vertex 1 is correct", result->distance[1] == 3);
        print_test_result("Shortest distance to final vertex is correct", result->distance[5] == 13);
        dijkstra_result_free(result);
    }
    graph_free(graph);
}

void run_path_reconstruction_tests(void) {
    Graph* graph = graph_create(5);
    print_test_result("Path reconstruction graph can be created", graph != NULL);
    if (graph == NULL) return;
    graph_add_undirected_edge(graph, 0, 1, 2);
    graph_add_undirected_edge(graph, 1, 3, 3);
    graph_add_undirected_edge(graph, 3, 4, 4);
    graph_add_undirected_edge(graph, 0, 2, 10);
    graph_add_undirected_edge(graph, 2, 4, 20);
    DijkstraResult* result = dijkstra_shortest_path(graph, 0);
    if (result != NULL) {
        PathResult* path = reconstruct_path(result, 4);
        print_test_result("Path reconstruction returns a path", path != NULL);
        if (path != NULL) {
            print_test_result("Path length is correct", path->length == 4);
            print_test_result("Path total cost is correct", path->total_cost == 9);
            print_test_result("Path starts and ends correctly", path->path[0] == 0 && path->path[3] == 4);
            path_result_free(path);
        }
        dijkstra_result_free(result);
    }
    graph_free(graph);
}

void run_robustness_tests(void) {
    Graph* graph = graph_create(4);
    print_test_result("Robustness test graph can be created", graph != NULL);
    if (graph == NULL) return;
    graph_add_undirected_edge(graph, 0, 1, 5);
    graph_add_undirected_edge(graph, 1, 2, 5);
    DijkstraResult* invalid_start = dijkstra_shortest_path(graph, -1);
    print_test_result("Invalid start vertex is handled safely", invalid_start == NULL);
    DijkstraResult* result = dijkstra_shortest_path(graph, 0);
    if (result != NULL) {
        PathResult* invalid_destination = reconstruct_path(result, 10);
        print_test_result("Invalid destination is handled safely", invalid_destination == NULL);
        PathResult* unreachable_path = reconstruct_path(result, 3);
        print_test_result("Unreachable destination returns no path", unreachable_path == NULL);
        dijkstra_result_free(result);
    }
    graph_free(graph);
}

void run_all_tests(void) {
    total_tests = passed_tests = failed_tests = 0;
    run_graph_tests();
    run_priority_queue_tests();
    run_dijkstra_tests();
    run_path_reconstruction_tests();
    run_robustness_tests();
    printf("\nTotal tests run: %d\n", total_tests);
    printf("Total passed: %d\n", passed_tests);
    printf("Total failed: %d\n", failed_tests);
    if (failed_tests == 0 && total_tests == 24) printf("Result: All 24 unit tests passed.\n");
}
