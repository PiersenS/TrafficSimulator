/* Vertex.h
*  Represents roadway intersections
*/

#ifndef Vertex_H
#define Vertex_H

#include "Edge.h"
#include <vector>


namespace ts {
    
    class Edge;

    class Vertex {
    private:
        std::vector<ts::Edge> edges;
        int junction; // Vertex number - junction numbers
    public:
        Vertex();                       // constructor
        int operator*();                // returns element associated with vertex - idk about return type yet
        bool operator==(Vertex v);
        std::vector<ts::Edge> incidentEdges();   // returns edge list of vertex
        bool isAdjacentTo(Vertex v);    // true if Vertex is adjacent to v
        void setJunction(int num);
    };

}

#endif