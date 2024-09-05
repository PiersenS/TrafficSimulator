#ifndef Car_H
#define Car_H

#include "Vertex.h"
#include <SFML/Graphics.hpp>


class Car : public sf::Sprite {
private:
    static const std::string textures[6];
    float speed;
    float direction; // angle of rotation
    float scaleFactor;
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

    void setCurrentVertex(ts::Vertex v);
    void setDestination(ts::Vertex v);

    ts::Vertex generateDestination(ts::Vertex current);

    void move(float x, float y);
};
#endif