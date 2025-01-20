/* C++ includes */
#include <vector>
/* Simulator includes */
#include "MovableEntity.h"
#include "ts_utils.h"

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

    int vertexChoice = ts::random(0, vertices.size());
    ts::Vertex v = vertices.at(vertexChoice);
    
    return v;
}