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
    vector<vector<Vertex>> adjMatrix;
    /* For adjMatrix:
    *   I think 2D vector of Vertex objects would 
    *   allow for easy indexing
    *   BUT: each vector would need a member variable to keep track of it's position in matrix
    *       - basically row header
    */
    /* 
    * I've been struggling with whether adjMatrix should be Edge objects or Vertex objects
    * I'm pretty sure it should be Vertices, since the job of the adjMatrix is to determine
    *   which Vertices are adjacent
    */
    
    void updateJunctions(int n);
public:
    Graph();
    Graph(vector<vector<Vertex>> matrix);
    vector<Vertex> getVertices();
    vector<Edge> getEdges();
    
    void setMatrix(vector<vector<Vertex>> matrix);
    void insertVertex(Vertex v);
    void insertEdge(Edge e, Vertex origin, Vertex dest);

    void removeVertex(Vertex v);
    void removeEdge(Edge e);
};

#endif