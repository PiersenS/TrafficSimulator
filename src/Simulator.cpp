/* main.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
#include "Graph.h"
#include "Car.h"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace ts;

void updateDelta();
void init(); // initializes simulator values

sf::Clock deltaClock;
sf::Vector2f startingPosition;
double delta;
float laneWidth;

int main() {
    cout << "Traffic Simulator started." << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    Graph graph("k4");

    init();
    
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../maps/k4/k4.png");

    string title = "Traffic Simulator";
    sf::VideoMode mode(710, 710);
    sf::RenderWindow window(mode, title);
    
    sf::Sprite background(backgroundTexture);
    background.setPosition(0,0);

    Car car;
    car.setScaleFactor(laneWidth / car.getLocalBounds().width);
    
    sf::Event event;
    while (window.isOpen()) {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        updateDelta();
        sf::Vector2f pos = car.getPosition();
        //cout << "Car position: (" << pos.x << ", " << pos.y << ")" << endl;

        //car.move(delta * car.getSpeed(), 0);

        window.clear();
        window.draw(background);
        window.draw(car);
        window.display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asSeconds();
}

void init() {
    startingPosition = sf::Vector2f(612, 80);
    laneWidth = 15.0;
}