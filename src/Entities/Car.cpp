/*
*   Implementation of Car.h
*/

/* C++ includes */
#include <iostream>
#include <random>
#include <cmath>
/* Simulator includes */
#include "Car.h"
#include "../Utils/ts_utils.h"

using namespace sf;

const int PRECISION = 1000;

const std::string Car::textures[6] = {"black","blue","green","yellow"};

Car::Car() {
    speed = 100;
    rotation = 0.0;
    direction = sf::Vector2f(0, -1);
    position = sf::Vector2f(620, 300);
    texture = randomCar();
    state = PARKED;

    setTexture(texture);
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2); // set origin of sprite to middle
    setRotation(rotation);
    setPosition(position);
}

// TODO: dir should no longer be a float (I don't remember why - as of 9/26/24)
Car::Car(sf::Texture t, sf::Vector2f pos, float dir) {
    speed = 100;
    rotation = dir;
    position = pos;
    texture = t;
    state = PARKED;

    setTexture(texture);
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setRotation(rotation);
    setPosition(position);
}

Texture Car::randomCar() {
    using namespace std;

    string colorChoice = textures[ts::random(0, 3)];
    int numChoice = ts::random(1, 5);

    Texture t;
    t.loadFromFile("assets/Cars/car_" + colorChoice + "_small_" + to_string(numChoice) + ".png");
    return t;
}

void Car::setScaleFactor(float factor) {
    scaleFactor = factor;
    setScale(scaleFactor, scaleFactor);
}

/********************* Accessors *********************/
Vector2f Car::getPosition()             { return position; }
float Car::getSpeed()                   { return speed; }
sf::Vector2f Car::getDirection()        { return direction; }
ts::Vertex* Car::getDestination()       { return destVertex; }
ts::Vertex* Car::getCurrentVertex()     { return currentVertex; }
Car::State Car::getState()              { return state; }
bool Car::isRunning()                   { return running; }

/********************* Mutators *********************/
void Car::setDirection(sf::Vector2f dir)    { direction = dir; }
void Car::start() { 
    // alive = true;
    running = true;
    state = PARKED;
}
void Car::stop() {  running = false; }
void Car::setRandomDestination(ts::Graph* graph) {
    destVertex = graph->randAdjVertex(currentVertex);
}
// void Car::kill()                            { alive = false; }
void Car::setDriving()                      { state = DRIVING;}
void Car::setParking()                      { state = PARKING;}
void Car::setParked()                       { state = PARKED;}

/********************* Overloaded sf::Sprite functions *********************/
void Car::move(float x, float y) {
    float newX = position.x + x;
    float newY = position.y + y;
    position = Vector2f(newX, newY);
    sf::Sprite::move(x, y);
}

void Car::move(sf::Vector2f v) {
    position += v;
    sf::Sprite::move(v);
}

void Car::rotate(float deg) {
    // update direction vector
    
    // to rotate 90 degrees: flip sin or cos (depending on virtical/horizontal)
    // Try rotating 90 degrees to the left (-90)
    // - flip sin?
    float degree = this->getRotation() + deg;
    float rad = degree * (M_PI/180);

    // flip sin & cos for 90 deg rotation
    float x = round(sin(rad) * PRECISION) / PRECISION;
    float y = round(-cos(rad) * PRECISION) / PRECISION;

    // direction = Vector2f(x, y);
    this->setDirection(Vector2f(x, y));
    sf::Sprite::rotate(deg);
}
