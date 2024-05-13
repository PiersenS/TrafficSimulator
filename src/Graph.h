#ifndef Graph_H
#define Graph_H

#include "Vertex.cpp"
#include "Edge.cpp"
#include <string>
#include <vector>
using namespace std;

class Graph {
private:
    vector<Vertex> vertices;
    vector<Edge> edges;
public:
    Graph();
    vector<Vertex> getVertices();
    vector<Edge> getEdges();
    
    void insertVertex(Vertex v);
    void insertEdge(Edge e, Vertex origin, Vertex dest);

    void removeVertex(Vertex v);
    void removeEdge(Edge e);
};

#endif