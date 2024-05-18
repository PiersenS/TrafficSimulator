#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <algorithm>

using namespace std;

Vertex::Vertex() {
    // still don't know what's going to go here
    /* TODO: overload constructor
    *  - do after making Graph.cpp
    *  - bc how do we get the incident edges?
    */
    junction = 0;
}

int Vertex::operator*() {
    // returns element associated with Vertex
    // maybe vertex num?
    return junction;
}

vector<Edge> Vertex::incidentEdges() {
    return edges;
}

bool Vertex::isAdjacentTo(Vertex v){
    /* return true if this and v share an edge
    * for each incident, 
    * return true if found in Vertex v's incident edges
    *   else return false
    */
    vector<Edge>::iterator iter;
    for (Edge e : edges) {
        iter = find(v.edges.begin(), v.edges.end(), e);
        if (iter != v.edges.end()) {
            return true;
        }
    }
    return false;
}