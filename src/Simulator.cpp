/* Simulator.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

/* C++ includes */
#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
#include <typeinfo>
/* Custom header files */
#include "Graph.h"
#include "Car.h"
#include "RoadSegment.h"
#include "Test.h"
#include "ts_utils.h"
/* SFML */
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ts;

string sim_map;
string windowTitle;
sf::VideoMode* videoMode;
sf::RenderWindow* window;
sf::Sprite* background;
sf::Texture* backgroundTexture;

sf::Thread* thread;

void updateDelta();
void handleEvent(sf::Event event);
/* Simulator setup */
void setup(); // initializes simulator values
void loadBoundaries();
void placeRoadSegments();
/* MovableEntity functions*/
void addCar();
void drive(MovableEntity* entity);

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<string,sf::RectangleShape> boundaries;
std::vector<ts::RoadSegment> roadSegments;
std::vector<Car*> cars;
float delta;
float laneWidth, roadWidth;

int main() {
    cout << "Traffic Simulator started!" << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    // Graph graph("k4");

    setup();

    // addCar();
    
    bool turn = false;
    
    std::cout << "Starting loop . . . " << std::endl;
    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        handleEvent(event);
        
        updateDelta();

        // Test::orbitWithVectors(car, delta, roadSegments); // doesn't orbit yet :( -- need more direction from Car, graph, etc.

        window->clear();
        window->draw(*background);
        // window->draw(car);
        Test::drawCars(*window, cars);
        for (Car* c : cars) {
            window->draw(*c);
        }
        Test::drawBoundaries(*window, boundaries);
        // Test::drawRoadSegments(*window, roadSegments);
        window->display();
    }
    
    return 0;
} // end of main

void updateDelta() {
    delta = deltaClock.restart().asSeconds();
}

void handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed) {
        cout << "Traffic Simulator ending . . ." << endl;
        window->close();
        exit(0);
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            addCar();
        }
    }
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
    ts::RoadSegment* rs = NULL;
    sf::Vector2f* in = NULL; 
    sf::Vector2f* out = NULL;
    while (!ifs.eof()) {
        ifs >> x >> y >> height >> width >> oneWay;
        rs = new ts::RoadSegment(sf::Vector2f(x, y), height, width);
        // generate vectors
        if (oneWay) {
            // idk
        }
        else { // biway
            if (height > width) {
                std::cout << "Height > Width" << std::endl;
                in = new sf::Vector2f(0, height);
                out = new sf::Vector2f(0, -height);
            }
            else { 
                std::cout << "Width > Height" << std::endl;
                in = new sf::Vector2f(width, 0);
                out = new sf::Vector2f(-width, 0);
            }

            rs->setIncoming(in);
            rs->setOutgoing(out);

            /* Unhandled Edge Case: x = y */
            /* Unhandled situation: diagonal roads
            *       - just rotate vector and include rotation in txt file 
            *       - reference Car.cpp for vector rotations
            */
        }

        roadSegments.push_back(*rs);
    }
    ifs.close();

    // Test::printRoadSegments(roadSegments);
}

void addCar() {
    /** Steps:
     * Init car
     * pick spawn?
     * create thread - call drive()
     */
    Car* car = new Car();
    car->setScaleFactor(laneWidth / car->getLocalBounds().width);

    car->start();
    cars.push_back(car);

    thread = new sf::Thread(*drive, car);
    thread->launch();

    std::cout << cars.size() << " cars have been added." << std::endl;
}

void drive(MovableEntity* entity) {
    if (typeid(*entity) == typeid(Car)) {
        Car* car = dynamic_cast<Car*>(entity);
        float carDelta;
        sf::Clock carClock;
        while (car->isAlive()) {
            ts::restartDelta(carDelta, carClock);
            Test::orbit(*car, carDelta, boundaries);
        }
    }
    else {
        std::cout << "entity is not a car" << std::endl;
    }
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