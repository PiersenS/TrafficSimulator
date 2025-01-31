/*
*   Test.h
*   Holds functions used for testing
*/

#ifndef Test_H
#define Test_H

#include "Car.h"
#include "Graph.h"
#include "RoadSegment.h"
#include <SFML/Graphics.hpp>

class Test {
public:
    static int frameCounter;
    /* Move */
    static void moveCar(Car& car, float& delta);
    static void moveBtoA(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries);
    static void moveWithKeyboard(sf::Event::EventType et, Car& car, float& delta);
    /* Orbit */
    static void orbit(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries);
    static void orbitWithVectors(Car& car, float& delta, std::vector<ts::RoadSegment>& roadSegments);
    /* Draw */
    static void drawBoundaries(sf::RenderWindow& window, std::map<string,sf::RectangleShape>& boundaries);
    static void drawRoadSegments(sf::RenderWindow& window, std::vector<ts::RoadSegment>& roadSegments);
    /* Print */
    static void printRoadSegments(std::vector<ts::RoadSegment>& roadSegments);
    static void printRoadSegmentVectors(std::vector<ts::RoadSegment>& roadSegments);
    static void printVector(sf::Vector2f v);
};

#endif