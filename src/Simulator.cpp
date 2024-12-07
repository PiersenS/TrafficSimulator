/* Simulator.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

// I/O
#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
// Custom header files
#include "Graph.h"
#include "Car.h"
#include "Test.h"
// SFML
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ts;

void updateDelta();
void init(); // initializes simulator values
void loadBoundaries(string map);

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<string,sf::RectangleShape> boundaries;
float delta;
float laneWidth;

int main() {
    cout << "Traffic Simulator started!" << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    // Graph graph("k4");

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
    
    bool turn = false;
    
    sf::Event event;
    while (window.isOpen()) {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            cout << "Traffic Simulator ending . . ." << endl;
            window.close();
            return 0;
        }
        updateDelta();
        
        Test::moveWithKeyboard(event.type, car, delta);
        cout << "(" << car.getPosition().x << ", " << car.getPosition().y << ")" << endl;
        // Test::moveBtoA(car, delta, boundaries);
        //Test::orbit(car, delta, boundaries);

        window.clear();
        window.draw(background);
        window.draw(car);
        Test::drawBoundaries(window, boundaries);
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

    loadBoundaries("k4");
}

void loadBoundaries(string map) {
    ifstream ifs;
    ifs.open("../maps/" + map + "/boundaries.txt");

    // vars for processing each line
    vector<string> segments;
    string line;
    stringstream sstream;
    string seg;
    while(getline(ifs, line)) {
        sstream.str(line);
        // parse line into individual strings
        while (getline(sstream, seg, ' ')) {
            segments.push_back(seg);
        }
        
        sstream.clear();
        string name = segments.at(0);
        int width = stoi(segments.at(1));
        int height = stoi(segments.at(2));

        int x = stoi(segments.at(3));
        int y = stoi(segments.at(4));

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(width, height));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color(0,0,0,50));

        boundaries[name] = rect;

        segments.clear();
    }
    ifs.close();
}

/*  NOTES:

    Right now, bounding boxes are added to each Vertex (intersection).
    However, the map is not being loaded into the Graph yet. 

    Steps:
    (1) Load k4 map into Graph
    (2) Implement CurrentVertex feature for the car
    (3) Draw car.getCurrentVertex().getBoundaryRect();



Controlling Cars:
    - maybe move each Car "forward" in the loop
    - use methods to change direction and rotation

*/