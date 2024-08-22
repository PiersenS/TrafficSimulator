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

void updateDelta();

sf::Clock deltaClock;
double delta;

int main() {
    cout << "Traffic Simulator started." << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    Graph graph("k4");
    
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../maps/k4/k4.png");

    string title = "Traffic Simulator";
    sf::VideoMode mode(640, 480);
    sf::RenderWindow window(mode, title);
    
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/green_car.png")) {
        cout << "Failed to load green_car.png" << endl;
        return 1;
    }
    
    sf::Sprite background(backgroundTexture);
    sf::Sprite car(texture);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        updateDelta();

        car.move(delta, 0);

        window.clear();
        window.draw(background);
        window.draw(car);
        window.display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asMilliseconds();
}
