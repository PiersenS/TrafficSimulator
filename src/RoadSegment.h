/**
 * RoadSegment.h
 * Holds bounding boxes and direction vectors for each Road
 * 
 * RoadSegment object will sit on top of Edge
 */

// SFML includes
#include <SFML/Graphics.hpp>

namespace ts {
    
    class RoadSegment {
    private:
        sf::Vector2f* incoming;
        sf::Vector2f* outgoing;
        sf::RectangleShape* boundary;

        sf::Vector2f position;   // location on map - center of RoadSegement (bounding box)
        float length, width;

    public:
        /* Constructors */
        RoadSegment();
        RoadSegment(sf::Vector2f pos, float length, float width);

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