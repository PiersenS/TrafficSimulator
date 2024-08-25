#ifndef Car_H
#define Car_H

#include "Vertex.h"
#include <SFML/Graphics.hpp>

using GraphVertex = Graph::Vertex;

class Car : public sf::Sprite {
private:
    static const std::string textures[6];
    float speed;
    float direction; // angle of rotation
    float scaleFactor;
    sf::Vector2f position;
    sf::Texture texture;

    Vertex currentVertex;
    Vertex destination;

    static sf::Texture randomCar();

public:
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    void setScaleFactor(float factor);
    sf::Vector2f getPosition();
    float getSpeed();

    Vertex getCurrentVertex();
    Vertex getDestination();

    void setCurrentVertex(Vertex v);
    void setDestination(Vertex v);

    Vertex generateDestination(Vertex current);
};
#endif