/*
*   Implementation of Test.h functions
*/

#include "Test.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

void Test::moveAndTurn(Car& car, float& delta, bool turnLeft, bool turnRight) {
    car.move(car.getDirection() * car.getSpeed() * delta);
}

void Test::moveBtoA(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries) {
    if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
        float rotation = -90;
        // rotate to the left 90 degrees
        // remember to adjust direction vector
        // float sine = sin(rotation);
        // Vector2f newDir = car.getDirection() * sine;

        // car.setDirection(newDir);
        // std::cout << "Direction vector: (" << car.getDirection().x << ", "
        //           << car.getDirection().y << ")" << std::endl;
        car.rotate(rotation);
    }

    moveAndTurn(car, delta, false, false);


}

void Test::moveWithKeyboard(sf::Event::EventType et, Car& car, float& delta) {
    using namespace sf;
    float speed = car.getSpeed();
    if (et == Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                car.setRotation(-90);
                car.move(-speed * delta, 0);
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            car.setRotation(90);
            car.move(speed * delta, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.setRotation(0);
            car.move(0, -speed * delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.setRotation(180);
            car.move(0, speed * delta);
        }
    }
}

void Test::drawBoundaries(sf::RenderWindow& window, std::map<string,sf::RectangleShape>& boundaries) {
    map<string, sf::RectangleShape>::iterator iter = boundaries.begin();
    while (iter != boundaries.end()) {
        window.draw(iter->second);
        iter++;
    }
}