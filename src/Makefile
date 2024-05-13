CC= g++
CFLAGS= -g -std=c++11

#lookupserver: 	lookupserver.o fifo.o Bible.o Ref.o Verse.o
#	$(CC) $(CFLAGS) -o lookupserver fifo.o Ref.o Verse.o Bible.o lookupserver.o

all: Graph.o

Graph.o: Vertex.h Edge.h Graph.cpp Graph.h
	$(CC) $(CFLAGS) -c Graph.cpp