/**
 * Road.h
 * Holds bounding boxes and direction vectors for each Road
 *
 */

// SFML includes
#include <SFML/Graphics.hpp>

namespace ts {
    
    class Road {
    private:
        sf::Vector2f* incoming;
        sf::Vector2f* outgoing;
        sf::RectangleShape* boundary;

        void setIncoming(sf::Vector2f& in);
        void setOutgoing(sf::Vector2f& out);
        void setBoundary(sf::RectangleShape& rect);

    public:
        sf::Vector2f& getIncoming();
        sf::Vector2f& getOutgoing();
        sf::RectangleShape& getBoundary();
    };
}