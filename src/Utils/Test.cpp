/*
*   Implementation of Test.h functions
*/
/* C++ */
#include <cmath>
#include <iostream>
/* TS */
#include "Test.h"
#include "ts_utils.h"

int Test::frameCounter = 0;

/* Car Movement Functions */
void Test::moveCar(Car& car, float& delta) {
    car.move(car.getDirection() * car.getSpeed() * delta);
}

void Test::moveBtoA(Car& car, float& delta, std::map<std::string,sf::RectangleShape>& boundaries) {
    if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
        car.rotate(-90);
    }
    moveCar(car, delta);
}

void Test::orbit(Car& car, float& delta, std::map<std::string,sf::RectangleShape>& boundaries) {
    float rotation = -90;

    if (car.getGlobalBounds().intersects(boundaries["BA"].getGlobalBounds())) {
        car.rotate(rotation);
    }
    if (car.getGlobalBounds().intersects(boundaries["AD"].getGlobalBounds())) {
        car.rotate(rotation);
    }
    if (car.getGlobalBounds().intersects(boundaries["DC"].getGlobalBounds())) {
        car.rotate(rotation);
    }
    if (car.getGlobalBounds().intersects(boundaries["CB"].getGlobalBounds())) {
        car.rotate(rotation);
    }
    if (car.getGlobalBounds().intersects(boundaries["B"].getGlobalBounds())) {
        car.setState(Car::State::PARKING);
    }
    moveCar(car, delta);
}

void Test::exitOrbit(Car& car, float& delta) {
    // travel a few more pixels, turn right, kill when off screen

    if (car.getRotation() != 90) {
        float turnPosY = 372;
        if (car.getPosition().y <= turnPosY) {
            car.rotate(90);
        }
    }
    moveCar(car, delta);
    if (car.getPosition().x > 750) {
        car.setState(Car::State::PARKED);
    }
}

void Test::orbitWithVectors(Car& car, float& delta, std::vector<ts::RoadSegment>& roadSegments) {
    ts::RoadSegment* current = NULL;
    sf::FloatRect carBounds = car.getGlobalBounds();

    for (ts::RoadSegment rs : roadSegments) {
        if (carBounds.intersects(rs.getBoundary()->getGlobalBounds())) {
            current = &rs;
            break;
        }
    }
    if (current == NULL) {
        // Ran off the road
        return;
    }
    printVector(*current->getOutgoing());

    sf::Vector2f norm = ts::normalize(*current->getOutgoing());
    car.move(norm * car.getSpeed() * delta);
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

/* Movement with Graph */
void Test::followPath(Car& car, float& delta, std::vector<ts::RoadSegment>& roadSegments, std::vector<ts::Vertex>& path) {
    std::cout << "followPath entered." << std::endl;
    /* Read path from beginning to end. path[0] will be the Vertex the car should be traveling to.
     * path[0] is reached, erase path[0] to begin traveling to the next vertex
     */

    Test::printRoadSegments(roadSegments);

    if (path.empty()) {
        std::cout << "Empty path, unable to set a destination." << std::endl;
        return;
    }

    ts::RoadSegment* segment;
    ts::Vertex dest = path.at(0);
    sf::FloatRect carBounds = car.getGlobalBounds();

    for (int i = 0; i < roadSegments.size(); i++) {
        if (carBounds.intersects(roadSegments.at(i).getBoundary()->getGlobalBounds())) {
            segment = &roadSegments.at(i);
            break;
        }
    }
    // should now have the current RoadSegment
    if (segment == NULL) {
        // Ran off the road
        return;
    }

    std::cout << "Segment = (" << segment->getPosition().x << ", " << segment->getPosition().y << ")" << std::endl;

    // get edge - determine which way to go
    std::cout << segment->getEdges().size() << " edges for Segment\n";
    std::vector<ts::Edge*> edges = segment->getEdges(); // NOTE: edges has 0 edges (idk why) - seg fault in for each loop
    ts::Edge* edge;
    for (ts::Edge* e : edges) {
        std::cout << "In foreach loop\n";
        if (*e == *car.getCurrentEdge()) {
            // then this is the edge I need and my edge is on this road segment
            std::cout << "Edge found - trying to assign it to variable." << std::endl;
            edge = e;
            std::cout << "Edge found!" << std::endl;
        }
    }
    // for loop skips and seg fault occurs here
    sf::Vector2f* direction;
    if (dest == *edge->getOrigin()) {
        direction = segment->getIncoming();
    }
    else if (dest == *edge->getDest()) {
        direction = segment->getOutgoing();
    }
    else {
        // something went wrong
        std::cout << "path[0] was neither the current edge's origin or destination vertex." << std::endl;
        std::cout << "returning from Test::followPath." << std::endl;
        return;
    }

    // TODO: figure out what happens when the end of the vector is reached.
    
    sf::Vector2f norm = ts::normalize(*direction);
    car.move(norm * car.getSpeed() * delta);

}

/* Draw Functions */
void Test::drawBoundaries(sf::RenderWindow& window, std::map<std::string,sf::RectangleShape>& boundaries) {
    std::map<std::string, sf::RectangleShape>::iterator iter = boundaries.begin();
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
void Test::drawCars(sf::RenderWindow& window, std::vector<Car*>& cars) {
    for (Car* c : cars) {
        window.draw(*c);
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

        cout << "Edges: [ ";
        for (ts::Edge* e : rs.getEdges()) {
            cout << e->getName() << " ";
        }
        cout << "]" << endl;
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
