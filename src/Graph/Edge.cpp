#include "Edge.h"
#include "Vertex.h"
#include <vector>
#include <algorithm>

using namespace ts;

Edge::Edge() {
    name = "";
}

Edge::Edge(std::string name) {
    this->name = name;
}

Edge::Edge(std::string name, double length, int speedLimit, bool directed) {
    this->name = name;
    this->length = length;
    this->speedLimit = speedLimit;
    this->directed = directed;
    this->state = State::UNEXPLORED;
}

std::string Edge::operator*() {
    return this->name;
}

bool Edge::operator==(const Edge e) {
    return this->name == e.name;
}

bool Edge::operator==(const Edge* e) {
    return this->name == e->name;
}

std::vector<Vertex> Edge::endVertices() {
    return {origin, dest};
}

Vertex* Edge::opposite(Vertex* v) {
    // returns Vertex on opposite end of v
    if (isIncidentOn(*v)) {
        // compare junctions, not objects
        if (**v == **origin) {
            return dest;
        }
        else {
            return origin;
        }
    }
    return NULL;
}

bool Edge::isAdjacentTo(Edge e) {
    /* two edges are adjacent when they share a vertex */
    // (1) get end vertices for this edge and e
    // (2) see if they have one of the same end vertices
    std::vector<Vertex> otherEnds = e.endVertices();
    for (Vertex v : otherEnds) {
        if (v == *origin || v == *dest) {
            return true;
        }
    }
    return false;
}

bool Edge::isIncidentOn(Vertex v) {
    // true if v == origin or dest
    std::vector<Edge*> ie = v.incidentEdges();
    for (Edge* e : ie) {
        if (v == *e->origin || v == *e->dest)
        return true;
    }
    return false;
}

/* -------------------- Accessors -------------------- */
Vertex* Edge::getOrigin()           { return this->origin; }
Vertex* Edge::getDest()             { return this->dest; }
std::string Edge::getName()         { return this->name; }
double Edge::getLength()            { return this->length; }
int Edge::getSpeedLimit()           { return this->speedLimit; }
bool Edge::isDirected()             { return this->directed; }
Edge::State Edge::getState()        { return this->state; }
// sf::Vector2f Edge::getDirection()   { return this->dirVector; }

/* -------------------- Mutators -------------------- */
void Edge::setOrigin(Vertex* origin)  { this->origin = origin; }
void Edge::setDest(Vertex* dest)      { this->dest = dest; }
void Edge::setName(std::string name)        { this->name = name; }
void Edge::setLength(double length)         { this->length = length; }
void Edge::setSpeedLimit(int sl)            { speedLimit = sl; }
void Edge::setDirected(bool directed)       { this->directed = directed; }
void Edge::setState(Edge::State s)  { this->state = s; }
// void Edge::setDirection(float x, float y)   { dirVector = sf::Vector2f(x, y); }
