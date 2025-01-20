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
#include "RoadSegment.h"
#include "Test.h"
// SFML
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ts;

string sim_map;
string windowTitle;
sf::VideoMode* videoMode;
sf::RenderWindow* window;
sf::Sprite* background;
sf::Texture* backgroundTexture;

void updateDelta();
void setup(); // initializes simulator values
void loadBoundaries();
void placeRoadSegments();

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<string,sf::RectangleShape> boundaries;
std::vector<ts::RoadSegment> roadSegments;
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
    
    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        if (event.type == sf::Event::Closed) {
            cout << "Traffic Simulator ending . . ." << endl;
            window->close();
            return 0;
        }
        updateDelta();

        // Test::orbit(car, delta, boundaries);
        Test::orbitWithVectors(car, delta, roadSegments);

        window->clear();
        window->draw(*background);
        window->draw(car);
        // Test::drawBoundaries(*window, boundaries);
        Test::drawRoadSegments(*window, roadSegments);
        window->display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asSeconds();
}

void setup() {
    std::cout << "Running setup . . ." << std::endl;

    /* Simulation */
    sim_map = "k4";
    startingPosition = sf::Vector2f(612, 80);
    laneWidth = 15.0;
    roadWidth = laneWidth * 2;

    /* Rendering */
    backgroundTexture = new sf::Texture();
    string path = "../maps/" + sim_map + "/" + sim_map + ".png";
    if (backgroundTexture->loadFromFile(path)) {
        std::cout << "Background Texture Loaded." << std::endl;
    }
    else {
        std::cout << "There was an error loading Background Textures. Exiting the program." << std::endl;
        exit(1);
    }

    background = new sf::Sprite(*backgroundTexture);

    windowTitle = "Traffic Simulator";
    videoMode = new sf::VideoMode(710, 710);
    window = new sf::RenderWindow(*videoMode, windowTitle);

    /* Map Setup */
    loadBoundaries();
    // placeRoadSegments();
}

void placeRoadSegments() {
    using namespace std;
    cout << "Creating RoadSegments . . . " << endl;
    ifstream ifs;
    string path = "../maps/" + sim_map + "/roadSegments.txt";
    ifs.open(path);

    int x, y, height, width, oneWay;
    ts::RoadSegment* rs;
    sf::Vector2f* in; 
    sf::Vector2f* out;
    while (!ifs.eof()) {
        ifs >> x >> y >> height >> width >> oneWay;
        rs = new ts::RoadSegment(sf::Vector2f(x, y), height, width);
        // generate vectors
        if (oneWay) {
            // idk
        }
        else {
            int start; 
            if (height > width) {
                in = new sf::Vector2f(0, height);
                out = new sf::Vector2f(0, -height);
            }
            else { 
                in = new sf::Vector2f(width, 0);
                out = new sf::Vector2f(-width, 0);
            }
            cout << "Setting Incoming and Outgoing vectors." << endl;
            rs->setIncoming(*in);
            rs->setOutgoing(*out);
            /* Unhandled Edge Case: x = y */
            /* Unhandled situation: diagonal roads
            *       - just rotate vector and include rotation in txt file 
            *       - reference Car.cpp for vector rotations
            */
        }

        roadSegments.push_back(*rs);
        cout << "Road Segment created." << endl;
    }
    ifs.close();
}


/* loadBoundaries() will eventually be deleted */
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