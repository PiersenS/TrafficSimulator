/* C++ includes */
#include <vector>
/* Simulator includes */
#include "MovableEntity.h"
#include "../Utils/ts_utils.h"

/* Accessors */
bool MovableEntity::isAlive() { return alive; }
ts::Edge* MovableEntity::getCurrentEdge()               { return currentEdge; }
ts::Vertex* MovableEntity::getCurrentVertex()           { return currentVertex; }
ts::Vertex* MovableEntity::getDestinationVertex()       { return destVertex; }
ts::Vertex* MovableEntity::getNextDestination()         { return nextDestVertex; }

/* Mutators */
void MovableEntity::setCurrentEdge(ts::Edge* e)         { currentEdge = e; }
void MovableEntity::setCurrentVertex(ts::Vertex* v)     { currentVertex = v; }
void MovableEntity::setDestinationVertex(ts::Vertex* v) { destVertex = v; }
void MovableEntity::setNextDestination(ts::Vertex* v)   { nextDestVertex = v; }
