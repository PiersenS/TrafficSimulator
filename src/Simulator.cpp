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
void placeBoundaries();

// TESTING FUNCTIONS
void moveWithKeyboard(sf::Event::EventType et, Car& car);
void moveSpriteWithKeyboard(sf::Event::EventType et, sf::Sprite& car);
void drawBoundaries(sf::RenderWindow& windows);
void moveBtoA(Car& car, bool turn);

sf::Clock deltaClock;
sf::Vector2f startingPosition;
std::map<string,sf::RectangleShape> boundaries;
double delta;
float laneWidth;

int main() {
    cout << "Traffic Simulator started!" << endl;
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
    
    bool turn = false;
    
    sf::Event event;
    while (window.isOpen()) {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            cout << "Traffic Simulator ending . . ." << endl;
            window.close();
        }
        moveWithKeyboard(event.type, car);
        updateDelta();
        
        cout << "Position: (" << car.getPosition().x << ", " << car.getPosition().y << ")" << endl;

        if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
            turn = true;
        }

        moveBtoA(car, turn);

        window.clear();
        window.draw(background);
        window.draw(car);
        drawBoundaries(window);
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

    // function to create boundaries
    placeBoundaries();
}

void moveBtoA(Car& car, bool turn) {
    int x, y;
    sf::RectangleShape aJunct = boundaries["A"];
    if (!car.getGlobalBounds().intersects(aJunct.getGlobalBounds())) {
        if (turn) {
            car.setRotation(-90);
            x = -car.getSpeed();
            y = 0;
        }
        else {
            car.setRotation(0);
            x = 0;
            y = -car.getSpeed();
        }
        car.move(x * delta, y * delta);
    }
}

void moveWithKeyboard(sf::Event::EventType et, Car& car) {
    using namespace sf;
    if (et == Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                car.setRotation(-90);
                car.move(-car.getSpeed() * delta, 0);
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            car.setRotation(90);
            car.move(car.getSpeed() * delta, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            car.setRotation(0);
            car.move(0, -car.getSpeed() * delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            car.setRotation(180);
            car.move(0, car.getSpeed() * delta);
        }
    }
}

void moveSpriteWithKeyboard(sf::Event::EventType et, sf::Sprite& car) {
    using namespace sf;
    float speed = 100;
    if (et == Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                car.setRotation(-90);
                car.move(-speed * delta, 0);
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            car.setRotation(90);
            car.move(speed * delta, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.setRotation(0);
            car.move(0, -speed * delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.setRotation(180);
            car.move(0, speed * delta);
        }
    }
}

void drawBoundaries(sf::RenderWindow& window) {
    map<string, sf::RectangleShape>::iterator iter = boundaries.begin();
    while (iter != boundaries.end()) {
        window.draw(iter->second);
        iter++;
    }
}

void placeBoundaries() {
    using namespace sf;

    RectangleShape A, B, C, D;
    RectangleShape Mid;

    RectangleShape AB, AC, AD;
    RectangleShape BA, BC, BD;
    RectangleShape CA, CB, CD;
    RectangleShape DA, DB, DC;

    A.setSize(Vector2f(64, 64));
    A.setPosition(320, 64);

    B.setSize(Vector2f(64, 64));
    B.setPosition(576, 320);

    C.setSize(Vector2f(64, 64));
    C.setPosition(320, 576);

    D.setSize(Vector2f(64, 64));
    D.setPosition(64, 320);

    Mid.setSize(Vector2f(64, 64));
    Mid.setPosition(320,320);

    AB.setSize(Vector2f(10, 20));
    AB.setPosition(632, 75);

    BA.setSize(Vector2f(20, 10));
    BA.setPosition(610, 62);

    BC.setSize(Vector2f(20, 10));
    BC.setPosition(610, 632);

    AD.setSize(Vector2f(10, 20));
    AD.setPosition(62, 75);
    
    DA.setSize(Vector2f(20, 10));
    DA.setPosition(75, 62);

    CB.setSize(Vector2f(10, 20));
    CB.setPosition(632, 608);

    CD.setSize(Vector2f(10, 20));
    CD.setPosition(62, 608);

    DC.setSize(Vector2f(20, 10));
    DC.setPosition(75, 632);



    boundaries["A"] = A;
    boundaries["B"] = B;
    boundaries["C"] = C;
    boundaries["D"] = D;
    boundaries["Mid"] = Mid;
    boundaries["BA"] = BA;
    boundaries["AB"] = AB;
    boundaries["AD"] = AD;
    boundaries["DA"] = DA;
    boundaries["BC"] = BC;
    boundaries["CB"] = CB;
    boundaries["CD"] = CD;
    boundaries["DC"] = DC;


    map<string, sf::RectangleShape>::iterator iter = boundaries.begin();
    while (iter != boundaries.end()) {
        RectangleShape& cur = iter->second;
        cur.setFillColor(sf::Color(0,0,0,50));
        iter++;
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