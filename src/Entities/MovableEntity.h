#ifndef MOVABLE_ENTITY_H
#define MOVABLE_ENTITY_H

/* Simulator includes */
#include "../Graph/Vertex.h"
/* SFML includes */
#include <SFML/Graphics.hpp>

class MovableEntity : public sf::Sprite {
protected:
    bool alive;
    float speed;
    float rotation; // angle of rotation
    float scaleFactor;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Texture texture;

    ts::Edge* currentEdge;
    ts::Vertex* currentVertex;
    ts::Vertex* destVertex;

public:
    /* Accessors */
    bool isAlive();
    ts::Edge* getCurrentEdge();
    ts::Vertex* getCurrentVertex();

    /* Mutators */
    virtual void setCurrentEdge(ts::Edge* e);
    virtual void setCurrentVertex(ts::Vertex* v);
    virtual void setDestinationVertex(ts::Vertex* v);
};

#endif
