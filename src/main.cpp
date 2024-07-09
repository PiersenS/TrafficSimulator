/* main.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

#include <iostream>
#include <Graph.h>

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

   Graph graph(loadMap("mvnu"));

    return 0;
} // end of main

vector<vector<Edge>> loadMap(string map) {
    // read in file
    string path = "maps/" + map + ".json"; // not sure if I'm going to use JSON or not
    return vector<vector<Edge>>();
}