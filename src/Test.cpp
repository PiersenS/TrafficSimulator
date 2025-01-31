/*
*   Implementation of Test.h functions
*/

#include "Test.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int Test::frameCounter = 0;

/* Car Movement Functions */
void Test::moveCar(Car& car, float& delta) {
    car.move(car.getDirection() * car.getSpeed() * delta);
}

void Test::moveBtoA(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries) {
    if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
        car.rotate(-90);
    }
    moveCar(car, delta);
}

void Test::orbit(Car& car, float& delta, std::map<string,sf::RectangleShape>& boundaries) {
    float rotation = -90;
    //if (frameCounter == 0) {

        if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["AD"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["DC"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
        if (car.getGlobalBounds().intersects(boundaries["CB"].getGlobalBounds())) {
            car.rotate(rotation);
            //frameCounter = 10;
        }
    //}
    moveCar(car, delta);
}

void Test::orbitWithVectors(Car& car, float& delta, std::vector<ts::RoadSegment>& roadSegments) {
    ts::RoadSegment current;
    sf::FloatRect carBounds = car.getGlobalBounds();
    current = roadSegments.at(0);
    printVector(*current.getIncoming());
    printVector(*current.getOutgoing());

    

    // sf::Vector2f carMvmt = 


    //for (ts::RoadSegment rs : roadSegments) {
    //    if (carBounds.intersects(rs.getBoundary()->getGlobalBounds())) {
    //        current = rs;
    //        break;
    //    }
    //}
    // std::cout << "Selected vector: (" << current.getIncoming()->x << ", " << current.getIncoming()->y << ")" << std::endl;
    // car.move(*current.getIncoming() * car.getSpeed() * delta);
}


// This doesn't properly move the car - use car.rotate() to update direction vector
// it also moves very....very....very slow
void Test::moveWithKeyboard(sf::Event::EventType et, Car& car, float& delta) {
    using namespace sf;
    float speed = car.getSpeed();
    if (et == Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            car.setRotation(-90);
            // car.move(-speed * delta, 0);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            car.setRotation(90);
            // car.move(speed * delta, 0);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.setRotation(0);
            // car.move(0, -speed * delta);
            moveCar(car, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.setRotation(180);
            // car.move(0, speed * delta);
            moveCar(car, delta);
        }
    }
}

/* Draw Functions */
void Test::drawBoundaries(sf::RenderWindow& window, std::map<string,sf::RectangleShape>& boundaries) {
    map<string, sf::RectangleShape>::iterator iter = boundaries.begin();
    while (iter != boundaries.end()) {
        window.draw(iter->second);
        iter++;
    }
}
void Test::drawRoadSegments(sf::RenderWindow& window, std::vector<ts::RoadSegment>& roadSegments) {
    using namespace ts;
    for (RoadSegment rs : roadSegments) {
        window.draw(*rs.getBoundary());
    }
}

/* Print Functions */
void Test::printRoadSegments(std::vector<ts::RoadSegment>& roadSegments) {
    using namespace std;
    int h, w;
    sf::Vector2f pos, in, out;
    ts::RoadSegment rs;
    for (int i = 0; i < roadSegments.size(); i++) {
        rs = roadSegments.at(i);
        h = rs.getHeight();
        w = rs.getWidth();
        pos = rs.getPosition();
        in = *rs.getIncoming();
        out = *rs.getOutgoing();

        printf("RoadSegment %d:\n"
               "\tPosition: (%f, %f)\n"
               "\tHeight: %d\n"
               "\tWidth: %d\n"
               "\tIncoming Vector: (%f, %f)\n"
               "\tOutgoing Vector: (%f, %f)\n", 
               i + 1, 
               pos.x, pos.y,
               h, w,
               in.x, in.y,
               out.x, out.y);
        cout << endl;
    }
}

void Test::printRoadSegmentVectors(std::vector<ts::RoadSegment>& roadSegments) {
    std::cout << "Printing all RoadSegment vectors: " << std::endl;
    for (ts::RoadSegment rs : roadSegments) {
        std::cout << "\t(" << rs.getIncoming()->x << ", " << rs.getIncoming()->y << ")" << std::endl;
    }
}

void Test::printVector(sf::Vector2f v) {
    using namespace std;
    cout << "(" << v.x << ", " << v.y << ")" << endl;
}