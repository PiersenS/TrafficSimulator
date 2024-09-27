#ifndef Car_H
#define Car_H

#include "Vertex.h"
#include <SFML/Graphics.hpp>


class Car : public sf::Sprite {
private:
    static const std::string textures[6];
    float speed;
    float rotation; // angle of rotation
    float scaleFactor;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Texture texture;

    ts::Vertex currentVertex;
    ts::Vertex destination;

    static sf::Texture randomCar();

public:
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    void setScaleFactor(float factor);
    sf::Vector2f getPosition();
    float getSpeed();

    ts::Vertex getCurrentVertex();
    ts::Vertex getDestination();

    void setDirection(sf::Vector2f dir);
    sf::Vector2f getDirection();

    void setCurrentVertex(ts::Vertex v);
    void setDestination(ts::Vertex v);

    ts::Vertex generateDestination(ts::Vertex current);

    // Overloaded sf::Sprite functions
    void move(float x, float y);
    void move(sf::Vector2f v);
    void rotate(float deg);
};
#endif