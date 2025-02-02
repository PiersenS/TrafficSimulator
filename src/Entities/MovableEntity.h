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
    ts::Vertex generateDestination(ts::Vertex* current);

    /* Accessors */
    bool isAlive();

    /* Mutators */
    void start();
    void kill();
};

#endif