/* Vertex.h
*  Represents roadway intersections
*/

#ifndef Vertex_H
#define Vertex_H

#include "Edge.h"
#include <vector>
#include <SFML/Graphics.hpp>

namespace ts {
    
    class Edge;

    class Vertex {
    public:
        enum State { UNEXPLORED, EXPLORED };

        Vertex();                       // constructor
        Vertex(std::string name);
        Vertex(std::string name, int junction);
        int operator*();                // returns element associated with vertex - idk about return type yet
        bool operator==(Vertex v);
        std::vector<ts::Edge*> incidentEdges();   // returns edge list of incident edges
        bool isAdjacentTo(Vertex v);    // true if Vertex is adjacent to v
        void setJunction(int num);
        int addJunction();

        /* Accessors */
        std::string getName();
        sf::FloatRect getBoundaries();
        State getState();

        /* Mutators */
        void setState(Vertex::State s);

    private:
        std::vector<ts::Edge*> edges;
        int junction; // Vertex number - junction numbers
        std::string name;
        sf::RectangleShape boundaryRect;
        State state;
    };
}

#endif
