/**
 * RoadSegment.cpp
 * Implementation of RoadSegement.h
 * Holds bounding boxes and direction vectors for each Road
 * 
 */

#include <iostream>
#include "RoadSegment.h"

using namespace ts;

RoadSegment::RoadSegment() {
    position = sf::Vector2f(0,0);
    height = 0;
    width = 0;

    incoming = NULL;
    outgoing = NULL;
}

RoadSegment::RoadSegment(sf::Vector2f pos, float height, float width) {
    this->position = pos;
    this->height = height;
    this->width = width;

    incoming = NULL;
    outgoing = NULL;

    boundary = new sf::RectangleShape();
    boundary->setSize(sf::Vector2f(width, height));
    boundary->setPosition(position);
    boundary->setFillColor(sf::Color(0,0,0,50)); // grey
}

/********************* Accessors *********************/
sf::Vector2f* RoadSegment::getIncoming()        { return incoming; }
sf::Vector2f* RoadSegment::getOutgoing()        { return outgoing; }
sf::Vector2f RoadSegment::getPosition()         { return position; }
sf::RectangleShape* RoadSegment::getBoundary()  { return boundary; }
float RoadSegment::getHeight()                  { return height; }
float RoadSegment::getWidth()                   { return width; }
std::vector<ts::Edge*> RoadSegment::getEdges()  { return edges; }

/********************* Mutators *********************/
void RoadSegment::setIncoming(sf::Vector2f* in)         { incoming = in; }
void RoadSegment::setOutgoing(sf::Vector2f* out)        { outgoing = out; }
void RoadSegment::setBoundary(sf::RectangleShape* rect) { boundary = rect; }
void RoadSegment::setEdges(std::vector<ts::Edge*> v)    { edges = v; }
