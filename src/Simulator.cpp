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
void moveWithKeyboard(sf::Event::EventType et, Car& car);
void moveSpriteWithKeyboard(sf::Event::EventType et, sf::Sprite& car);

void moveBtoA(Car& car, bool turn);

sf::Clock deltaClock;
sf::Vector2f startingPosition;
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

    sf::RectangleShape abCorner;
    abCorner.setFillColor(sf::Color::Red);
    abCorner.setSize(sf::Vector2f(20, 10));
    abCorner.setPosition(610, 60);

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

        if (car.getGlobalBounds().intersects(abCorner.getGlobalBounds())) {
            turn = true;
        }

        moveBtoA(car, turn);

        window.clear();
        window.draw(background);
        window.draw(car);
        window.draw(abCorner);
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

void moveBtoA(Car& car, bool turn) {
    int x, y;
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