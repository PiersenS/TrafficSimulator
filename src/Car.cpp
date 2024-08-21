/*
*   Implementation of Car.h
*/

#include "Car.h"
#include <random>

using namespace sf;

//const std::string MyClass::myArray[3]
// const std::string Car::textures[6] = {"pink", "orange", "green", "teal", "blue", "purple"};
const std::string Car::textures[6] = {"black","blue","green","yellow"};

Car::Car() {
    using namespace std;
    // apply random texture - random car color'
    random_device rand_dev;
    uniform_int_distribution<int> carColorDist(0,3);
    uniform_int_distribution<int> carNumberDist(1,5);
    string colorChoice = textures[carColorDist(rand_dev)];
    int numChoice = carNumberDist(rand_dev);

    Texture texture;
    texture.loadFromFile("../assets/Cars/car_" + colorChoice + "_" + to_string(numChoice) + ".png");
    
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