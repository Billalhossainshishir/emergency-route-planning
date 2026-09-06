# Emergency Route Planning in C

A portfolio version of my University of Tasmania data structures and algorithms project. It models a road network as a weighted adjacency-list graph and finds the lowest-cost route using Dijkstra's shortest-path algorithm and a binary-heap priority queue.

## Highlights

- Weighted adjacency-list graph implementation in C
- Dijkstra shortest-path search
- Binary min-heap priority queue
- Route reconstruction from predecessor links
- Handling of invalid and unreachable destinations
- 24 unit tests covering graph operations, queue behaviour, shortest paths, route reconstruction and robustness

## Project structure

```text
src/
  graph.c
  graph.h
  priority_queue.c
  priority_queue.h
  search.c
  search.h
  main.c

tests/
  tests.c
  tests.h

Makefile
```

## Build and run

Using `make`:

```bash
make
./route_planner
```

Run the test suite:

```bash
make test
```

Or compile directly with GCC:

```bash
gcc -std=c11 -Wall -Wextra src/graph.c src/priority_queue.c src/search.c src/main.c tests/tests.c -Isrc -Itests -o route_planner
```

## Example approach

The program stores roads as weighted edges. Dijkstra's algorithm repeatedly selects the currently cheapest unvisited vertex from a min-heap, relaxes neighbouring edges, and stores predecessor vertices so the final route can be reconstructed.

## Skills demonstrated

`C` · `Graphs` · `Dijkstra` · `Binary Heap` · `Priority Queue` · `Algorithms` · `Unit Testing` · `Memory Management`

## Note

This repository is a cleaned portfolio version of my completed project. University assessment instructions and IDE-generated build files are intentionally not included.
