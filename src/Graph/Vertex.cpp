#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include <vector>
#include <algorithm>

using namespace ts;

Vertex::Vertex() {
    // still don't know what's going to go here
    /* TODO: overload constructor
    *  - do after making Graph.cpp
    *  - bc how do we get the incident edges?
    */
    this->junction = addJunction();
    boundaryRect.setSize(sf::Vector2f(120,120));

}

Vertex::Vertex(std::string name) {
    this->name = name;
    this->junction = addJunction();
    state = State::UNEXPLORED;
}

Vertex::Vertex(std::string name, int junction) {
    this->name = name;
    this->junction = junction;
}

int Vertex::operator*() {
    // returns element associated with Vertex
    // maybe vertex num?
    return junction;
}

bool Vertex::operator==(Vertex v) {
    return this->junction == v.junction;
}

std::vector<Edge*> Vertex::incidentEdges() {
    return edges;
}

bool Vertex::isAdjacentTo(Vertex v){
    /* return true if this and v share an edge
    * for each incident, 
    * return true if found in Vertex v's incident edges
    *   else return false
    */
    std::vector<Edge*>::iterator iter;
    for (Edge* e : edges) {
        iter = find(v.edges.begin(), v.edges.end(), e);
        if (iter != v.edges.end()) {
            return true;
        }
    }
    return false;
}

void Vertex::setJunction(int num) {
    /* Used to reassign junction number
    *  when a vertex is removed, it is removed from the adjacency matrix
    *   to keep adj. matrix balanced, junct nums must be adjusted
    *   for all vertices with junct nums higher than the one being removed.
    */
   this->junction = num;
}

void Vertex::setState(Vertex::State s) { this->state = s; }

int Vertex::addJunction() {
    Graph::addJunction();
    return Graph::getNumJunctions();
}

std::string ts::Vertex::getName()           { return name; }
sf::FloatRect ts::Vertex::getBoundaries()   { return boundaryRect.getGlobalBounds(); }
ts::Vertex::State ts::Vertex::getState()    { return state; }
