#ifndef Graph_H
#define Graph_H

#include "Vertex.h"
#include "Edge.h"
// #include <string>
#include <vector>

namespace ts {

    class Graph {
    private:
        std::vector<Vertex*> vertexList;
        std::vector<Edge*> edgeList;
        std::vector<std::vector<int>> adjMatrix;
        std::vector<Vertex*> startingVertices;

        static int numJunctions;
        /* For adjMatrix:
        *   I think 2D std::vector of Vertex objects would 
        *   allow for easy indexing
        *   BUT: each std::vector would need a member variable to keep track of it's position in matrix
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
        Graph();
        Graph(std::string map);
        Graph(std::vector<std::vector<int>> matrix);

        /* Accessors */
        std::vector<ts::Vertex*> getVertices();
        std::vector<ts::Edge*> getEdges();
        ts::Edge* getEdge(std::string name);
        ts::Vertex* getStartingVertex();
        ts::Edge* getStartingEdge();

        /* Graph Functions */
        void setMatrix(std::vector<std::vector<int>> matrix);
        void addAdjacency(int originJunct, int destJunct, int edgeLength);

        bool insertVertex(Vertex* v);
        bool insertEdge(Edge* e, Vertex* origin, Vertex* dest);
        bool removeVertex(Vertex* v);
        bool removeEdge(Edge* e);

        std::vector<Vertex> bfs(Vertex current, Vertex dest);

        /* Simulator Functions */
        void loadMap(std::string map);
        ts::Vertex* randAdjVertex(ts::Vertex* current);
        ts::Vertex* getRandomVertex(ts::Vertex* current);

        /* Static Functions */
        static void addJunction();
        static void removeJunction();
        static int getNumJunctions();
    };
}
#endif
