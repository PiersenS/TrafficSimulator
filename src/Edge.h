/* Edge.h
*  Represents Roadways
*/

#ifndef Edge_H
#define Edge_H

#include "Vertex.h"
#include <vector>
#include <string>

using namespace std;

class Vertex;

class Edge {
private:
    Vertex* origin;
    Vertex* dest; // destination
    string name;
    double length;
    bool directed;
    
public: 
    Edge();                         // constructor
    Edge(string name);
    Edge(string name, double length);

    string operator*();                // returns element associated with edge - idk about return type yet
    bool operator==(const Edge e);
    vector<Vertex> endVertices();   // returns end vertices
    Vertex opposite(Vertex v);      // returns vertex on opposite end of v
    bool isAdjacentTo(Edge e);      // true if Edge is adjacent to e
    bool isIncidentOn(Vertex v);    // true if Edge is incident on vertex v
    bool isDirected();

    void setOrigin(Vertex origin);
    void setDest(Vertex dest);
    void setName(string name);
    void setDirected(bool directed);
};

#endif