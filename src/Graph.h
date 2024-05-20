#ifndef Graph_H
#define Graph_H

#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <vector>
using namespace std;

class Graph {
private:
    vector<Vertex> vertexList;
    vector<Edge> edgeList;
    vector<vector<bool>> adjMatrix;
    
    void updateJunctions(int n);
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