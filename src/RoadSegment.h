/**
 * RoadSegment.h
 * Holds bounding boxes and direction vectors for each Road
 * 
 * RoadSegment object will sit on top of Edge
 */

#ifndef ROAD_SEGMENT_H
#define ROAD_SEGMENT_H

// TS includes
#include "Edge.h"
// SFML includes
#include <SFML/Graphics.hpp>

namespace ts {
    
    class RoadSegment {
    private:
        ts::Edge* edge = NULL;
        sf::Vector2f* incoming = NULL;
        sf::Vector2f* outgoing = NULL;
        sf::RectangleShape* boundary = NULL;

        sf::Vector2f position;   // location on map - top left corner of RoadSegement (bounding box)
        float height, width;

    public:
        /* Constructors */
        RoadSegment();
        RoadSegment(sf::Vector2f pos, float height, float width);

        /* Accessors */
        sf::Vector2f* getIncoming();
        sf::Vector2f* getOutgoing();
        sf::RectangleShape* getBoundary();

        /* Mutators */
        void setIncoming(sf::Vector2f& in);
        void setOutgoing(sf::Vector2f& out);
        void setBoundary(sf::RectangleShape& rect);
    };
}

#endif