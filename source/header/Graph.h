#ifndef Graph_H
#define Graph_H

#include <string>
#include <vector>
using namespace std;

struct Node {
    /* Each node is an intersection
    *  store each node's neighbors
    *       - use vector of id's
    */
    int id;
    vector<int> adjacentNodes;
};

class Graph {
    /*
    * Reasons to use a header file for Graph:
    *   - implementing multiple graphs
    *   - abstraction for adjacency matrix, nodes, etc.
    */
};

#endif