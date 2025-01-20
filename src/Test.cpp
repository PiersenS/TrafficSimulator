/*
*   Implementation of Test.h functions
*/

#include "Test.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int Test::frameCounter = 0;

void Test::moveCar(Car& car, float& delta) {
    car.move(car.getDirection() * car.getSpeed() * delta);
}

void Test::moveBtoA(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries) {
    if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
        car.rotate(-90);
    }
    moveCar(car, delta);
}

void Test::orbit(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries) {
    float rotation = -90;
    //if (frameCounter == 0) {

        if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["AD"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["DC"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["CB"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
    //}
    moveCar(car, delta);
}

void Test::orbitWithVectors(Car& car, float& delta, std::vector<ts::RoadSegment>& roadSegments) {
    ts::RoadSegment current;
    sf::FloatRect carBounds = car.getGlobalBounds();
    for (ts::RoadSegment rs : roadSegments) {
        if (carBounds.intersects(rs.getBoundary()->getGlobalBounds())) {
            current = rs;
            break;
        }
    }
    car.move(*current.getIncoming());
}


// This doesn't properly move the car - use car.rotate() to update direction vector
// it also moves very....very....very slow
void Test::moveWithKeyboard(sf::Event::EventType et, Car& car, float& delta) {
    using namespace sf;
    float speed = car.getSpeed();
    if (et == Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            car.setRotation(-90);
            // car.move(-speed * delta, 0);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            car.setRotation(90);
            // car.move(speed * delta, 0);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.setRotation(0);
            // car.move(0, -speed * delta);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.setRotation(180);
            // car.move(0, speed * delta);
            moveCar(car, delta);
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
void Test::drawRoadSegments(sf::RenderWindow& window, std::vector<ts::RoadSegment>& roadSegments) {
    using namespace ts;
    for (RoadSegment rs : roadSegments) {
        window.draw(*rs.getBoundary());
    }
}