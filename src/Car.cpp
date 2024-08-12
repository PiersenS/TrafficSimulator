/*
*   Implementation of Car.h
*/

#include "Car.h"
#include <random>

using namespace sf;

//const std::string MyClass::myArray[3]
const std::string Car::textures[6] = {"pink", "orange", "green", "teal", "blue", "purple"};

Car::Car() {
    using namespace std;
    // apply random texture - random car color'
    random_device rand_dev;
    uniform_int_distribution<int> dist(0,5);
    string choice = textures[dist(rand_dev)];

    Texture texture;
    texture.loadFromFile("assets/" + choice + "_car.png");
    
    this->setTexture(texture);
}

Car::Car(Texture t) {
    this->setTexture(t);
}

void Car::setTexture(Texture t) {
    this->texture = t;
}

Texture Car::getTexture() {
    return this->texture;
}