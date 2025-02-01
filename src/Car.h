#ifndef Car_H
#define Car_H

/* Simulator includes */
#include "Vertex.h"
#include "MovableEntity.h"
/* SFML includes */
#include <SFML/Graphics.hpp>


class Car : public MovableEntity {
private:
    bool alive;
    static const std::string textures[6];
    static sf::Texture randomCar();
    /*
    float speed;
    float rotation; // angle of rotation
    float scaleFactor;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Texture texture;

    ts::Edge* currentEdge;
    ts::Vertex* currentVertex;
    ts::Vertex* destVertex;
    */

public:
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    void setScaleFactor(float factor);

    /* Accessors */
    sf::Vector2f getPosition();
    float getSpeed();
    sf::Vector2f getDirection();
    ts::Edge& getCurrentEdge();
    ts::Vertex& getCurrentVertex();
    ts::Vertex& getDestination();
    bool isAlive();

    /* Mutators */
    void setDirection(sf::Vector2f dir);
    void setCurrentEdge(ts::Edge* e);
    void setCurrentVertex(ts::Vertex& v);
    void setDestination(ts::Vertex& v);
    void start();
    void kill();

    // ts::Vertex generateDestination(ts::Vertex current);

    // Overloaded sf::Sprite functions
    void move(float x, float y);
    void move(sf::Vector2f v);
    void rotate(float deg);
};
#endif