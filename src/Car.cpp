/*
*   Implementation of Car.h
*/

#include "Car.h"
#include <random>

#include <iostream>

using namespace sf;

//const std::string MyClass::myArray[3]
// const std::string Car::textures[6] = {"pink", "orange", "green", "teal", "blue", "purple"};
const std::string Car::textures[6] = {"black","blue","green","yellow"};

Car::Car(sf::Texture& texture, sf::Vector2f pos, float dir) {
    speed = 20;
    direction = dir;
    position = pos;

    setTexture(texture);
    setRotation(direction);
    setPosition(position); // replace with position variable
}

Texture& Car::randomCar() {
    using namespace std;

    // apply random texture - random car color
    random_device rand_dev;
    uniform_int_distribution<int> carColorDist(0,3);
    uniform_int_distribution<int> carNumberDist(1,5);
    string colorChoice = textures[carColorDist(rand_dev)];
    int numChoice = carNumberDist(rand_dev);


    Texture *t;
    t->loadFromFile("../assets/Cars/car_" + colorChoice + "_small_" + to_string(numChoice) + ".png");
    return *t;
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