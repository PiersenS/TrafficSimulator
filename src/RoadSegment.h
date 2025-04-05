/**
 * RoadSegment.h
 * Holds bounding boxes and direction vectors for each Road
 * 
 * RoadSegment object will sit on top of Edge
 */

#ifndef ROAD_SEGMENT_H
#define ROAD_SEGMENT_H

/* C++ includes */
#include <vector>
/* TS includes */
#include "Graph/Edge.h"
/* SFML includes */
#include <SFML/Graphics.hpp>

namespace ts {
    
    class RoadSegment {
    private:
        ts::Edge* edge;
        sf::Vector2f* incoming;
        sf::Vector2f* outgoing;
        sf::RectangleShape* boundary;

        sf::Vector2f position;   // location on map - top left corner of RoadSegement (bounding box)
        float height, width;

        std::vector<ts::Vertex*> vertices;

    public:
        /* Constructors */
        RoadSegment();
        RoadSegment(sf::Vector2f pos, float height, float width);

        /* Accessors */
        sf::Vector2f* getIncoming();
        sf::Vector2f* getOutgoing();
        std::vector<Vertex*> getVertices();
        sf::Vector2f getPosition();
        sf::RectangleShape* getBoundary();
        float getHeight();
        float getWidth();
        ts::Edge getEdge();

        /* Mutators */
        void setIncoming(sf::Vector2f* in);
        void setOutgoing(sf::Vector2f* out);
        void setVertices(std::vector<Vertex*> v);
        void setBoundary(sf::RectangleShape* rect);
    };
}

#endif
