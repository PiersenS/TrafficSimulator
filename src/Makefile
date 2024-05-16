CC= g++
CFLAGS= -g -std=c++11

all: Graph

Graph: Graph.o Edge.o Vertex.o
	$(CC) $(CFLAGS) -o Graph Edge.o Vertex.o Graph.o

Edge.o: Vertex.h Edge.h Edge.cpp
	$(CC) $(CFLAGS) -c Edge.cpp

Vertex.o: Edge.h Vertex.h Vertex.cpp
	$(CC) $(CFLAGS) -c Vertex.cpp

Graph.o: Vertex.h Edge.h Graph.h Graph.cpp
	$(CC) $(CFLAGS) -c Graph.cpp