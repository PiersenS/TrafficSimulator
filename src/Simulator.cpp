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
#include "Graph/Graph.h"
#include "Entities/Car.h"
#include "RoadSegment.h"
#include "Utils/Test.h"
#include "Utils/ts_utils.h"
/* SFML */
#include <SFML/Graphics.hpp>

using namespace ts;

/* struct needed for findPath function */
struct PathFindingInfo {
    ts::Graph graph;
    Car* car;
    std::vector<ts::Vertex>* path;
};

ts::Graph* graph;

std::string sim_map;
std::string windowTitle;
sf::VideoMode* videoMode;
sf::RenderWindow* window;
sf::Sprite* background;
sf::Texture* backgroundTexture;

sf::Thread* driver;
sf::Thread* car_manager;

const int MAX_CARS = 50;

void updateDelta();
void handleEvent(sf::Event event);
/* Simulator setup */
void setup(); // initializes simulator values
void loadBoundaries();
void placeRoadSegments();
/* MovableEntity functions*/
void addCar();
void manageCars();
void drive(MovableEntity* entity);
void findPath(PathFindingInfo pfi);

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<std::string,sf::RectangleShape> boundaries;
std::vector<ts::RoadSegment> roadSegments;
std::vector<Car*> cars;
float delta;
float laneWidth, roadWidth;

int main() {
    std::cout << "Traffic Simulator started!" << std::endl;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    setup();
   
    car_manager = new sf::Thread(*manageCars);
    car_manager->launch();

    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        handleEvent(event);
        updateDelta();

        window->clear();
        window->draw(*background);
        for (Car* c : cars) {
            window->draw(*c);
        }
        // Test::drawBoundaries(*window, boundaries);
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
        std::cout << "Traffic Simulator ending . . ." << std::endl;
        window->close();
        exit(0);
    }
    // if (event.type == sf::Event::KeyPressed) {
    //     if (event.key.code == sf::Keyboard::Space) {
    //         addCar();
    //     }
    // }
}

void setup() {
    std::cout << "Running setup . . ." << std::endl;

    /* Simulation */
    sim_map = "k4";
    graph = new Graph(sim_map);
    startingPosition = sf::Vector2f(612, 80);
    laneWidth = 15.0;
    roadWidth = laneWidth * 2;

    /* Rendering */
    backgroundTexture = new sf::Texture();
    std::string path = "maps/" + sim_map + "/" + sim_map + ".png";
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
    placeRoadSegments();
}

void placeRoadSegments() {
    using namespace std;
    cout << "Creating RoadSegments . . . " << endl;

    /* setup file stream */
    ifstream ifs;
    stringstream ss;
    string line;
    string path = "maps/" + sim_map + "/roadSegments.txt";
    ifs.open(path);
    std::cout << "\tPath: " << path << std::endl;

    /* loop variables */
    int x, y, height, width, oneWay;
    ts::RoadSegment* rs = NULL;
    sf::Vector2f* in = NULL; 
    sf::Vector2f* out = NULL;

    /* Read from file and create objects */
    while (getline(ifs, line)) {
        ss.clear();
        ss.str(line);
        ss >> x >> y >> height >> width >> oneWay;

        // TODO: add edge to txt file and set RoadSegment.edge variable

        vector<ts::Vertex*> vertices;
        vector<ts::Edge*> rsEdges;

        rs = new ts::RoadSegment(sf::Vector2f(x, y), height, width);
        string edgeName;
        ts::Edge* cur;
        while (ss >> edgeName) {
            rsEdges.push_back(graph->getEdge(edgeName));
        }
        rs->setEdges(rsEdges);

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

        std::cout << "RS position:\n\t(" << rs->getPosition().x << ", " << rs->getPosition().y << ")\n";

        roadSegments.push_back(*rs);
    }
    ifs.close();

    Test::printRoadSegments(roadSegments);
}

void addCar() {
    /** Steps:
     * Init car
     * pick spawn?
     * create thread - call drive()
     */
    /* Initialize Car object */
    Car* car = new Car();
    car->setScaleFactor(laneWidth / car->getLocalBounds().width);

    car->start();
    cars.push_back(car);
    
    Vertex* v = graph->getStartingVertex();
    car->setCurrentVertex(v);
    
    /* Create Thread */
    driver = new sf::Thread(*drive, car);
    driver->launch();

    std::cout << "Car added. Total: " << cars.size() << std::endl;
}

void removeCar(Car* car) {
    // might have to exit thread
    std::vector<Car*>::iterator it;
    for (it = cars.begin(); it != cars.end(); it++) {
        if (*it == car) {
            car->stop();
            cars.erase(it);
            delete car;
            break;
        }
    }
    std::cout << "Car removed. Total: " << cars.size() << std::endl;
}

/**
 * Keep MAX_CARS cars on the map
 */
void manageCars() {
    std::cout << "car_manager started! " << std::endl;
    sf::Clock clock;
    sf::Time time;
    int carsAlive;

    clock.restart();    
    while(true) {
        carsAlive = cars.size();
        if (carsAlive < MAX_CARS) {
            // add car at random time interval
            int rand_seconds = ts::random(1, 6);
            sf::Time seconds = sf::seconds(rand_seconds);
            sf::sleep(seconds);

            addCar();
        }
    }
}

void drive(MovableEntity* entity) {
    if (typeid(*entity) == typeid(Car)) {
        Car* car = dynamic_cast<Car*>(entity);
        float carDelta;
        sf::Clock carClock;

        // std::vector<ts::Vertex> path;
        // sf::Thread* pathFinder;

        // car->setCurrentVertex(graph->getStartingVertex());
        // car->setCurrentEdge(graph->getStartingEdge());
        
        /* For debugging purposes
        if (!car->getCurrentEdge()->isIncidentOn(*car->getCurrentVertex())) {
            std::cout << "Somehow...the current edge is NOT incident on the current vertex." << std::endl;
            exit(0);
        }
        */

        // path.push_back(*car->getCurrentVertex()); // apparently this is needed
        
        /* Set up path-finding info */
        /*
        ts::Vertex* randomVertex = graph->getRandomVertex(car->getCurrentVertex());
        car->setDestinationVertex(randomVertex);
        // path.push_back(*randomVertex);

        car->setNextDestination(NULL);
        */

        car->setState(Car::State::DRIVING);
        while(car->isRunning()) {
            ts::restartDelta(carDelta, carClock);
            Car::State state = car->getState();
            switch(state) {
                case Car::State::DRIVING: { // need to define a scope to declare variables
                    Test::orbit(*car, carDelta, boundaries);
                    
                    /* The following code is commented since it handles the path-finding.
                     * To demonstrate the remaining components, a movement system using collision boundaries is used.
                     */
                    /*
                    if (car->getNextDestination() == NULL) {
                        // create thread to:
                        //      set nextDestination
                        //      bfs path
                        PathFindingInfo info;
                        info.graph = *graph;    // copy of graph
                        info.car = car;         // car pointer
                        info.path = &path;      // pointer to path - so path can be modified

                        pathFinder = new sf::Thread(*findPath, info);
                        pathFinder->launch();
                        
                    }

                    // print path vertices
                    std::cout << "path: [";
                    for (ts::Vertex v : path) {
                        std::cout << " " << v.getName();
                    }
                    std::cout << " ]" << std::endl;

                    Test::followPath(*car, carDelta, roadSegments, path);
                    */
                    
                    break;
                }
                case Car::State::ARRIVED:
                    car->setDestinationVertex(car->getNextDestination());
                    car->setNextDestination(NULL);
                    car->setState(Car::State::DRIVING);
                    break;
                case Car::State::PARKING:
                    Test::exitOrbit(*car, carDelta);
                    break;
                case Car::State::PARKED:
                    removeCar(car);
                    break;
            }
        }
        // while (car->getState() == Car::State::DRIVING) {
        //     ts::restartDelta(carDelta, carClock);
        //     // Test::orbit(*car, carDelta, boundaries);

        //     /* Cars need to have intention on where they're going. 
        //     how to do this? idk :(   */
        //     
        //     // how to relate edge to roadSegment?
        //     // choose incoming or outgoing?

        //     
        // }
        /*
        while(car->getState() == Car::State::PARKING) {
            // park car
            ts::restartDelta(carDelta, carClock);
            Test::exitOrbit(*car, carDelta);
        }
        // car is parked
        removeCar(car);
        */
    }
    // else -> pedestrian
}

void findPath(PathFindingInfo pfi) {
    // find path
    // append new path to the end of original path
    
}

/* loadBoundaries() will eventually be deleted */
void loadBoundaries() {
    using namespace std; // mostly reading from file
    ifstream ifs;
    ifs.open("maps/" + sim_map + "/boundaries.txt");

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
