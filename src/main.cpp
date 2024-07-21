/* main.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
#include "Graph.h"
// #include "../lib/csv.hpp"

using namespace std;

vector<vector<int>> loadMap(string map, vector<Vertex>& vertices, vector<Edge>& edges);

int main() {
    /*  Steps:
    *   (1) instantiate graph?
    *   (2) populate graph?
    *       - use configuration file for pre-made map of MVNU
    *       - might just be a table representing adj. matrix
    *   (3) idk...traverse?
    */

    cout << "Traffic Simulator started." << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    try {
        Graph graph(loadMap("k4", vertices, edges));
    } catch (runtime_error e) {
        cerr << e.what() << endl;
    }

    return 0;
} // end of main

vector<vector<int>> loadMap(string map, vector<Vertex>& vertices, vector<Edge>& edges) {
    // read in file
    string path = "maps/" + map + ".csv"; // not sure if I'm going to use JSON or not
    cout << "Loading Map: " << path << endl;
    
    // TODO: create outer vector
    vector<vector<int>> matrix;
    Vertex* v;

    ifstream ifs;
    string line;
    int numVertices, edgeLength;
    getline(ifs, line);         // first line - number of vertices
    numVertices = stoi(line);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            ifs >> edgeLength;
            matrix.at(i).at(j) = edgeLength;
        }
    }
    

    return matrix;
}