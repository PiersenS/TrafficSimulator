#ifndef Car_H
#define Car_H

/* Simulator includes */
#include "MovableEntity.h"
#include "../Graph/Graph.h"
/* SFML includes */
#include <SFML/Graphics.hpp>


class Car : public MovableEntity {

public:
    enum State { DRIVING, ARRIVED, PARKING, PARKED};

    /* Constructors */
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    
    /* Destructor */
    ~Car() {}

    /* Accessors */
    sf::Vector2f getPosition();
    float getSpeed();
    sf::Vector2f getDirection();
    ts::Vertex* getDestination();
    ts::Vertex* getCurrentVertex();
    State getState();
    bool isRunning();

    /* Mutators */
    void setScaleFactor(float factor);
    void setDirection(sf::Vector2f dir);
    // void setRandomDestination(ts::Graph* graph);
    void start();
    void stop();
    // void kill();
    void setState(Car::State state);

    // Overloaded sf::Sprite functions
    void move(float x, float y);
    void move(sf::Vector2f v);
    void rotate(float deg);

    /* Behavioral Functions */

private:
    Car::State state;
    bool running;
    static const std::string textures[6];
        
    static sf::Texture randomCar();
};
#endif
