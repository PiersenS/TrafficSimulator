/*
*   Implementation of Car.h
*/

#include "Car.h"
#include <random>

#include <iostream>

using namespace sf;

const std::string Car::textures[6] = {"black","blue","green","yellow"};

Car::Car() {
    speed = 100;
    rotation = 0.0;
    direction = sf::Vector2f(0, 1); // pointing up?
    position = sf::Vector2f(620, 388);
    texture = randomCar();

    setTexture(texture);
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setRotation(rotation);
    setPosition(position);
}

// TODO: dir should no longer be a float
Car::Car(sf::Texture t, sf::Vector2f pos, float dir) {
    speed = 100;
    rotation = dir;
    position = pos;
    texture = t;

    setTexture(texture);
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setRotation(rotation);
    setPosition(position);
}

Texture Car::randomCar() {
    using namespace std;

    // apply random texture - random car color
    random_device rand_dev;
    uniform_int_distribution<int> carColorDist(0,3);
    uniform_int_distribution<int> carNumberDist(1,5);
    string colorChoice = textures[carColorDist(rand_dev)];
    int numChoice = carNumberDist(rand_dev);

    Texture t;
    t.loadFromFile("../assets/Cars/car_" + colorChoice + "_small_" + to_string(numChoice) + ".png");
    return t;
}

void Car::setScaleFactor(float factor) {
    scaleFactor = factor;
    setScale(scaleFactor, scaleFactor);
}

void Car::move(float x, float y) {
    float newX = position.x + x;
    float newY = position.y + y;
    position = Vector2f(newX, newY);
    sf::Sprite::move(x, y);
}

void Car::move(sf::Vector2f v) {
    position = v;
    sf::Sprite::move(v);
}

Vector2f Car::getPosition() {
    return position;
}

float Car::getSpeed() {
    return speed;
}

ts::Vertex Car::getCurrentVertex() {
    return currentVertex;
}

void Car::setCurrentVertex(ts::Vertex v) {
    currentVertex = v;
}

ts::Vertex Car::getDestination() {
    return destination;
}

void Car::setDirection(sf::Vector2f dir) {
    direction = dir;
}

sf::Vector2f Car::getDirection() {
    return direction;
}