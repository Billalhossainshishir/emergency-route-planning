CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic
TARGET := route_planner

SOURCES := src/graph.c src/priority_queue.c src/search.c src/main.c tests/tests.c

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -Isrc -Itests -o $(TARGET)

test: $(TARGET)
	./$(TARGET) --tests

clean:
	rm -f $(TARGET)
