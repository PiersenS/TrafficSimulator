/* 
* Implementation of Graph.h
*/

// C++ std lib
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
// Simulator includes
#include "Graph.h"
#include "../Utils/ts_utils.h"

using namespace ts;

int Graph::numJunctions = 0;

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

void Graph::addAdjacency(int originJunct, int destJunct, int edgeLength) {
    // idk how yet.
    
}
    
bool Graph::insertVertex(Vertex v) {
    if (find(vertexList.begin(), vertexList.end(), v) != vertexList.end()) {    // if already in Vertex List
        return false;
    }

    vertexList.push_back(v);

    return true;
}
bool Graph::insertEdge(Edge e, Vertex origin, Vertex dest) {
    /* Maybe do some error checking
    *  see if origin and dest are in vertexList
    */
    // add Edge if not already in list
    if (find(edgeList.begin(), edgeList.end(), e) != edgeList.end()) {
        return false;
    }

    edgeList.push_back(e);

    // do I care if these return false? 
    // Wouldn't that just mean they were already there?
    //      So I can update adjacency matrix anyway?
    insertVertex(origin);
    insertVertex(dest);

    // update adjacency matrix
    addAdjacency(*origin, *dest, e.getLength());

   return true;
}

bool Graph::removeVertex(Vertex v) {
    vector<Vertex>::iterator pos = find(vertexList.begin(), vertexList.end(), v);
    vertexList.erase(pos);
    // udpate adjacency matrix
    // (1) erase vertexNum from adj. matrix.

    // (2) update all higher vertices with setJunction
    updateJunctions(*v);
    
    return true; // always returns true
}

bool Graph::removeEdge(Edge e) {
    vector<Edge>::iterator pos = find(edgeList.begin(), edgeList.end(), e);
    edgeList.erase(pos);
    // update adjacency matrix

    return true; // always returns true
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

/* Simulator Functions */
ts::Vertex* Graph::randAdjVertex(ts::Vertex* current) {
    using namespace ts;
    std::vector<Edge> incident = current->incidentEdges();
    std::vector<Vertex*> adj;
    Vertex* v;
    for (Edge e : incident) {
        *v = e.opposite(*current);
        adj.push_back(v);
    }

    int choice = ts::random(0, adj.size());
    return adj.at(choice);
}

void Graph::addJunction() {
    numJunctions++;
}

void Graph::removeJunction() {
    numJunctions--;
}

int Graph::getNumJunctions() {
    return numJunctions;
}

void Graph::loadMap(string map) {
    using namespace std;
    ifstream ifs;
    string path = "maps/" + map + "/graphData.txt";
    ifs.open(path);

    if (!ifs.is_open()) {
        cerr << "Unable to open graphData file: " << path << endl;
        exit(1);
    }

    int vertices, edges;
    ifs >> vertices >> edges;
    cout << vertices << " vertices. " << edges << " edges" << endl;

    string vertexName;
    for (int i = 0; i < vertices; i++) {    // process vertices
        ifs >> vertexName;
        cout << "Creating Vertex: " << vertexName << endl;
        Vertex v(vertexName, i); // name and junction number
        vertexList.push_back(v);
    }
    
    string edgeName, originName, destName;
    int speedLimit, isDirected;
    double length;
    bool directed;
    for (int i = 0; i < edges; i++) {       // process edges
        // take input
        ifs >> edgeName >> originName >> destName;
        ifs >> length >> speedLimit >> isDirected;
        cout << edgeName << " " << originName << " " << destName << " ";
        cout << length << " " << speedLimit << " " << isDirected << endl;
        directed = (bool) isDirected;

        // Create Edge and Vertices
        Edge* e = new Edge(edgeName, length, speedLimit, directed);
        Vertex* origin = new Vertex(originName);
        Vertex* destination = new Vertex(destName);

        cout << "Edge, origin, and destination created." << endl;
        
        e->setOrigin(origin);
        e->setDest(destination);

        cout << "Edge's origin and destination have been set." << endl;

        // insert Edge/Vertices in Graph
        insertEdge(*e, *origin, *destination); // inserts Edge, origin, & destination
        cout << "Edge inserted!" << endl;
    }
}

/*
    Try:
        skip reading in Vertices, since they are included with the Edges
        Instead, create vertices, store in vertex list, 
        and store pointer in Edge object
            - all of this can possibly be gathered from each
              edge description

*/

/*
Look at ~/Downloads/Graph.h for reference
    - How do they find individual vertices?


*/
