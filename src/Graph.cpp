/* 
* Implementation of Graph.h
*/

#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "csv.hpp"

using namespace std;

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
/*
// on second thought....maybe use csv-parser library
void Graph::loadMap(string map) {
    string path = "maps/" + map + ".csv"; // not sure if I'm going to use JSON or not
    cout << "Loading Map: " << path << endl;

    // IO
    ifstream ifs(path);
    if (!ifs) {
        throw runtime_error("Unable to open map file.");
    }
    string line;
    // Loop variables
    int numVertices, numEdges, edgeLength;
    Vertex* v;

    // read first line
    getline(ifs, line);
    numVertices = stoi(line);
    // read names of vertices
    for (int i = 1; i <= numVertices; i++) {
        getline(ifs, line);
        v = new Vertex();
        v->setJunction(i);
        vertexList.push_back(*v);
    }

    // get number of Edges
    getline(ifs, line);
    numEdges = stoi(line);
    Edge* e;
    stringstream ss;
    string edgeName, length;
    for (int i = 0; i < numEdges; i++) {
        getline(ifs, line); // get next line from file
        ss.str(line);
        // split line into edgeName / on second thought....maybe use csv-parser libraryand length
        getline(ss, edgeName, ' ');
        getline(ss, length, ' ');
        
        e = new Edge(edgeName, stod(length));
        edgeList.push_back(*e);
        // find a way to set origin and dest for each edge
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            ifs >> edgeLength;
            this->adjMatrix.at(i).at(j) = edgeLength;

            
        }
    }
}
*/

void Graph::loadMap(string map) {
    using namespace csv;
    string path = "maps/" + map + ".csv";
    cout << "Loading Map: " << path << endl;

    CSVReader reader(path);
    for (CSVRow row : reader) {        // for each row
        for (CSVField field : row) {   // for each column
            
        }
    }
}