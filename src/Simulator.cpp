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

string sim_map;
string windowTitle;
sf::VideoMode* videoMode;
sf::RenderWindow* window;
sf::Texture* backgroundTexture;
sf::Sprite* background;

void updateDelta();
void setup(); // initializes simulator values
void loadBoundaries();
void placeRoadSegments();

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<string,sf::RectangleShape> boundaries;
float delta;
float laneWidth, roadWidth;

int main() {
    cout << "Traffic Simulator started!" << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    // Graph graph("k4");

    setup();

    Car car;
    car.setScaleFactor(laneWidth / car.getLocalBounds().width);
    
    bool turn = false;

    background = new sf::Sprite(backgroundTexture);
    background->setPosition(0,0);
    
    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        if (event.type == sf::Event::Closed) {
            cout << "Traffic Simulator ending . . ." << endl;
            window->close();
            return 0;
        }
        updateDelta();
        
        Test::moveWithKeyboard(event.type, car, delta);
        // cout << "(" << car.getPosition().x << ", " << car.getPosition().y << ")" << endl;
        // Test::moveBtoA(car, delta, boundaries);
        Test::orbit(car, delta, boundaries);
        Test::orbitWithVectors(car, delta);

        sf::Sprite tempBack = *background;
        window->clear();
        window->draw(tempBack);
        window->draw(car);
        Test::drawBoundaries(*window, boundaries);
        window->display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asSeconds();
}

void setup() {
    /* Rendering */
    //sf::Texture backgroundTexture;
    if (!backgroundTexture->loadFromFile("../maps/k4/k4.png")) {
        std::cout << "SOMETHING WENT WRONG" << std::endl;
    }
    else {
        std::cout << "backgroundTexture loaded!" << std::endl;
    }

    windowTitle = "Traffic Simulator";
    videoMode = new sf::VideoMode(710, 710);
    window = new sf::RenderWindow(*videoMode, windowTitle);

    /* Simulation */
    sim_map = "k4";
    startingPosition = sf::Vector2f(612, 80);
    laneWidth = 15.0;
    roadWidth = laneWidth * 2;

    /* Map Setup */
    loadBoundaries();
    //placeRoadSegments();
}

void loadBoundaries() {
    ifstream ifs;
    ifs.open("../maps/" + sim_map + "/boundaries.txt");

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

void placeRoadSegments() {
    using namespace std;
    ifstream ifs;
    ifs.open("../maps/" + sim_map + "/roadSegments.txt");

    while (!ifs.eof()) {

    }
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