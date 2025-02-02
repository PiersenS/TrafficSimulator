#ifndef Graph_H
#define Graph_H

#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <vector>

namespace ts {

    class Graph {
    private:
        vector<Vertex> vertexList;
        vector<Edge> edgeList;
        vector<vector<int>> adjMatrix;

        static int numJunctions;
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
        * 
        * I think it should just be integers representing the weights (length) of the edges
        */

        void updateJunctions(int n);
    public:
        Graph(string map);
        Graph(vector<vector<int>> matrix);
        void loadMap(string map);
        vector<Vertex> getVertices();
        vector<Edge> getEdges();

        void setMatrix(vector<vector<int>> matrix);
        void addAdjacency(int originJunct, int destJunct, int edgeLength);

        bool insertVertex(Vertex v);
        bool insertEdge(Edge e, Vertex origin, Vertex dest);
        bool removeVertex(Vertex v);
        bool removeEdge(Edge e);

        /* Static Functions */
        static void addJunction();
        static void removeJunction();
        static int getNumJunctions();
    };
}
#endif