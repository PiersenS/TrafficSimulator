/*
*   Implementation of Car.h
*/

#include "Car.h"
#include <random>

#include <iostream>

using namespace sf;

const std::string Car::textures[6] = {"black","blue","green","yellow"};

Car::Car() {
    speed = 20;
    direction = 0.0;
    position = sf::Vector2f(612, 80);
    texture = randomCar();

    setTexture(texture);
    setRotation(direction);
    setPosition(position);
}

Car::Car(sf::Texture t, sf::Vector2f pos, float dir) {
    speed = 20;
    direction = dir;
    position = pos;
    texture = t;

    setTexture(texture);
    setRotation(direction);
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