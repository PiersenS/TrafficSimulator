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
    vector<vector<Edge>> adjMatrix;
    /* For adjMatrix:
    *   I think 2D vector of Edge objects would 
    *   allow for easy indexing
    *   BUT: each vector would need a mem. var. to keep track of it's position in matrix
    *       - basically row header
    */
    
    void updateJunctions(int n);
public:
    Graph();
    Graph(vector<vector<Edge>> matrix);
    vector<Vertex> getVertices();
    vector<Edge> getEdges();
    
    void setMatrix(vector<vector<Edge>> matrix);
    void insertVertex(Vertex v);
    void insertEdge(Edge e, Vertex origin, Vertex dest);

    void removeVertex(Vertex v);
    void removeEdge(Edge e);
};

#endif