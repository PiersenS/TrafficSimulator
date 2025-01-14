/**
 * RoadSegment.cpp
 * Implementation of RoadSegement.h
 * Holds bounding boxes and direction vectors for each Road
 * 
 */

#include "RoadSegment.h"

using namespace ts;

RoadSegment::RoadSegment() {
    position = sf::Vector2f(0,0);
    height = 0;
    width = 0;
}

RoadSegment::RoadSegment(sf::Vector2f pos, float height, float width) {
    this->position = pos;
    this->height = height;
    this->width = width;

    boundary = new sf::RectangleShape();
    boundary->setSize(sf::Vector2f(width, height));
    boundary->setPosition(position);
    boundary->setFillColor(sf::Color(0,0,0,50)); // grey
}

/********************* Accessors *********************/
sf::Vector2f* RoadSegment::getIncoming()        { return incoming; }
sf::Vector2f* RoadSegment::getOutgoing()        { return outgoing; }
sf::RectangleShape* RoadSegment::getBoundary()  { return boundary; }

/********************* Mutators *********************/
void RoadSegment::setIncoming(sf::Vector2f& in)         { *incoming = in; }
void RoadSegment::setOutgoing(sf::Vector2f& out)        { *outgoing = out; }
void RoadSegment::setBoundary(sf::RectangleShape& rect) { *boundary = rect; }
