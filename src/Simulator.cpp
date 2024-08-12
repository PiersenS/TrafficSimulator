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

    string title = "Traffic Simulator";
    sf::VideoMode mode(640, 480);
    sf::RenderWindow window(mode, title);

    /*
    sf::Color collisionColor(255, 100, 100);
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("assets/green_car.png")) {
        cout << "Failed to Load Green Car." << endl;
        cout << "Closing Window . . . " << endl;
        window.close();
    }

    sf::Sprite car(carTexture);
    car.setTexture(carTexture);
    */
    
    
    sf::Texture texture;
    texture.loadFromFile("assets/green_car.png");
    //Car car(texture);
    sf::Sprite car(texture);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        updateDelta();

        car.move(delta, 0);

        window.clear();
        window.draw(car);
        window.display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asMilliseconds();
}
