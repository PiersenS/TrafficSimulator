/* 
* Implementation of Graph.h
*/

// C++ std lib
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
// Custom header files
#include "Graph.h"

using namespace ts;

Graph::Graph(string map) {
    loadMap(map);
}

Graph::Graph(vector<vector<int>> matrix) {
    this->adjMatrix = matrix;
}

vector<Vertex> Graph::getVertices() {
    return this->vertexList;
}
vector<Edge> Graph::getEdges() {
    return this->edgeList;
}

void Graph::setMatrix(vector<vector<int>> matrix) {
    this->adjMatrix = matrix;
}
    
void Graph::insertVertex(Vertex v) {
    vertexList.push_back(v);
}
void Graph::insertEdge(Edge e, Vertex origin, Vertex dest) {
    /* Maybe do some error checking
    *  see if origin and dest are in vertexList
    */
   
}

void Graph::removeVertex(Vertex v) {
    vector<Vertex>::iterator pos = find(vertexList.begin(), vertexList.end(), v);
    vertexList.erase(pos);
    // udpate adjacency matrix
    // (1) erase vertexNum from adj. matrix.

    // (2) update all higher vertices with setJunction
    updateJunctions(*v);
}

void Graph::removeEdge(Edge e) {
    vector<Edge>::iterator pos = find(edgeList.begin(), edgeList.end(), e);
    edgeList.erase(pos);
    // update adjacency matrix
}


// TODO:
// I wrote updateJunctions when I was tired. 
// pls re-check logic
void Graph::updateJunctions(int n) {
    /* n is the junction of the removed vertex
    * row n and col n were deleted
    * update all junctions > n to equal their pos in adj. matrix
    */
    for (int i = 0; i < adjMatrix.size(); i++) {
        // for each vector in adjMatrix (each col)
        for (int j = n; j < adjMatrix.at(i).size(); j++) {
            
        }
    }
}

void Graph::loadMap(string map) {
    using namespace std;
    ifstream ifs;
    ifs.open("../maps/" + map + "/graphData.txt");

    int vertices, edges;
    ifs >> vertices >> edges;

    string vertexName;
    for (int i = 0; i < vertices; i++) {
        cin >> vertexName;
        
    }
    
    
}