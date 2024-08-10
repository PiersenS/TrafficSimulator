/* main.cpp
*  Contains the main function for the project
*  and acts as the driver for the graph
*/

#include <iostream>
#include <fstream> // filestream
#include <sstream> // string stream
#include <string>
#include "Graph.h"

#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    cout << "Traffic Simulator started." << endl;
    vector<Vertex> vertices;
    vector<Edge> edges;
    Graph graph("k4");

    string title = "Traffic Simulator";
    sf::VideoMode mode(640, 480);
    sf::RenderWindow window(mode, title);

    while (window.isOpen()) {

    }

    return 0;
} // end of main
