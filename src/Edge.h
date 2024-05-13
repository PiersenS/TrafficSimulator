/* Edge.h
*  Represents Roadways
*/

#ifndef Edge_H
#define Edge_H

#include "Vertex.cpp"
#include <vector>

using namespace std;

class Edge {
public: 
    Edge();                         // constructor
    int operator*();                // returns element associated with edge - idk about return type yet
    vector<Vertex> endVertices();   // returns end vertices
    Vertex opposite(Vertex v);      // returns vertex on opposite end of v
    bool isAdjacentTo(Edge e);      // true if Edge is adjacent to e
    bool isIncidentOn(Vertex v);    // true if Edge is incident on vertex v
};

#endif