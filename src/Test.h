/*
*   Test.h
*   Holds functions used for testing
*/

#ifndef Test_H
#define Test_H

#include "Car.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>

class Test {
public:
    static int frameCounter;
    static void moveCar(Car& car, float& delta);
    static void moveBtoA(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries);
    static void orbit(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries);
    static void orbitWithVectors(Car& car, float& delta);
    static void moveWithKeyboard(sf::Event::EventType et, Car& car, float& delta);
    static void drawBoundaries(sf::RenderWindow& window, std::map<string,sf::RectangleShape>& boundaries);
};

#endif