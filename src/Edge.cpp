#include "Edge.h"
#include "Vertex.h"
#include <vector>
#include <algorithm>

using namespace std;

Edge::Edge() {
    name = "";
}

Edge::Edge(string name) {
    this->name = name;
}

string Edge::operator*() {
    return this->name;
}

bool Edge::operator==(const Edge e) {
    if (this->name == e.name) {
        return true;
    }
    return false;
}

vector<Vertex> Edge::endVertices() {
    return {origin, dest};
}

Vertex Edge::opposite(Vertex v) {
    // returns Vertex on opposite end of v
    if (isIncidentOn(v)) {
        // compare junctions, not objects
        if (*v == **origin) {
            return *dest;
        }
        else {
            return *origin;
        }
    }
}

bool Edge::isAdjacentTo(Edge e) {
    /* two edges are adjacent when they share a vertex */
    // (1) get end vertices for this edge and e
    // (2) see if they have one of the same end vertices
    vector<Vertex> otherEnds = e.endVertices();
    for (Vertex v : otherEnds) {
        if (*v == **origin || *v == **dest) {
            return true;
        }
    }
    return false;
}

bool Edge::isIncidentOn(Vertex v) {
    // ---
}