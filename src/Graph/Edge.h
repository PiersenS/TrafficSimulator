/* Edge.h
*  Represents Roadways
*/

#ifndef Edge_H
#define Edge_H

// Graph Includes
#include "Vertex.h"
// SFML
#include <SFML/Graphics.hpp>
// CPP Includes
#include <vector>
#include <string>

namespace ts {

    class Vertex;
    
    class Edge {
    public: 
        enum State { UNEXPLORED, DISCOVERED, CROSS };

        Edge();                         // constructor
        Edge(std::string name);
        Edge(std::string name, double length, int speedLimit, bool directed);

        std::string operator*();                // returns element associated with edge - idk about return type yet
        bool operator==(const Edge e);
        std::vector<Vertex> endVertices();   // returns end vertices
        Vertex* opposite(Vertex* v);      // returns vertex on opposite end of v
        bool isAdjacentTo(Edge e);      // true if Edge is adjacent to e
        bool isIncidentOn(Vertex v);    // true if Edge is incident on vertex v

        /* Accessors */
        Vertex* getOrigin();
        Vertex* getDest();
        std::string getName();
        double getLength();
        int getSpeedLimit();
        bool isDirected();
        State getState();
        // sf::std::vector2f getDirection();

        /* Mutators */
        void setOrigin(Vertex* origin);
        void setDest(Vertex* dest);
        void setName(std::string name);
        void setLength(double length);
        void setSpeedLimit(int sl);
        void setDirected(bool directed);
        void setState(Edge::State s);
        // void setDirection(float x, float y);

    private:
        Vertex* origin;
        Vertex* dest; // destination
        std::string name;
        double length;
        int speedLimit;
        bool directed;
        sf::Vector2f dirVector; // direction vector
        State state;
    };
}

#endif
