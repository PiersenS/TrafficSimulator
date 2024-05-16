CC= g++
CFLAGS= -g -std=c++11

all: Graph

Graph: Graph.o Edge.o Vertex.o
	$(CC) $(CFLAGS) -o Graph Edge.o Vertex.o Graph.o

Edge.o: Edge.cpp Edge.h Vertex.h
	$(CC) $(CFLAGS) -c Edge.cpp

Vertex.o: Vertex.cpp Vertex.h Edge.h
	$(CC) $(CFLAGS) -c Vertex.cpp

Graph.o: Graph.cpp Graph.h Vertex.h Edge.h
	$(CC) $(CFLAGS) -c Graph.cpp


clean: 
	rm *.o