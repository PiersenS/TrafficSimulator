/* C++ includes */
#include <vector>
/* Simulator includes */
#include "MovableEntity.h"
#include "../Utils/ts_utils.h"

ts::Vertex MovableEntity::generateDestination(ts::Vertex* current) {
    /**
     * TODO:
     * Get all adjacent vertices
     * pick random one
     * 
     * For each incident edge, get opposite vertex
     */

    std::vector<ts::Edge> incidentEdges = current->incidentEdges();
    std::vector<ts::Vertex> vertices;

    for (ts::Edge e: incidentEdges) {
        vertices.push_back(e.opposite(*current));
    }

    //int vertexChoice = ts::random(0, vertices.size());
    //ts::Vertex v = vertices.at(vertexChoice);
    
    ts::Vertex v;
    return v;
}

/* Accessors */
bool MovableEntity::isAlive() { return alive; }

/* Mutators */
void MovableEntity::start()     { alive = true; }
void MovableEntity::kill()      { alive = false; }