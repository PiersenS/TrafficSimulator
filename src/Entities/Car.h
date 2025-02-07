#ifndef Car_H
#define Car_H

/* Simulator includes */
#include "MovableEntity.h"
/* SFML includes */
#include <SFML/Graphics.hpp>


class Car : public MovableEntity {

public:
    enum State { DRIVING, PARKING, PARKED};

    /* Constructors */
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    
    /* Destructor */
    ~Car() {}

    /* Accessors */
    sf::Vector2f getPosition();
    float getSpeed();
    sf::Vector2f getDirection();
    ts::Vertex& getDestination();
    State getState();

    /* Mutators */
    void setScaleFactor(float factor);
    void setDirection(sf::Vector2f dir);
    void start();
    void kill();
    void setDriving();
    void setParking();
    void setParked();

    // Overloaded sf::Sprite functions
    void move(float x, float y);
    void move(sf::Vector2f v);
    void rotate(float deg);

private:
    Car::State state;
    static const std::string textures[6];
    static sf::Texture randomCar();
};
#endif
