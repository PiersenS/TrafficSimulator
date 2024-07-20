/* main.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
#include "Graph.h"
#include "../lib/csv.hpp"

using namespace std;

vector<vector<Edge>> loadMap(string map);

int main() {
    /*  Steps:
    *   (1) instantiate graph?
    *   (2) populate graph?
    *       - use configuration file for pre-made map of MVNU
    *       - might just be a table representing adj. matrix
    *   (3) idk...traverse?
    */

    cout << "Traffic Simulator started." << endl;
    try {
        Graph graph(loadMap("k4"));
    } catch (runtime_error e) {
        cerr << e.what() << endl;
    }

    return 0;
} // end of main

vector<vector<Edge>> loadMap(string map) {
    using namespace csv;
    // read in file
    string path = "maps/" + map + ".csv"; // not sure if I'm going to use JSON or not
    cout << "Loading Map: " << path << endl;
    
    CSVReader reader(path);
    for (CSVRow& row : reader) {
        for (CSVField& field : row) {
            
        }
    }

    return vector<vector<Edge>>();
}