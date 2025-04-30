/* C++ includes */
#include <random>
#include <cmath>
#include <iostream>
/* Simulator includes */
#include "ts_utils.h"

int ts::random(int min, int max) {
    using namespace std;

    random_device rand_dev;
    uniform_int_distribution<int> uid(min, max);

    return uid(rand_dev);
}

sf::Vector2f ts::normalize(sf::Vector2f source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 1) {
        float norm_x = source.x / length;
        float norm_y = source.y / length;
        return sf::Vector2f(norm_x, norm_y); // normalized vector
    }
    return source; // source already normalized
}

void ts::restartDelta(float& delta, sf::Clock& clock) {
    delta = clock.restart().asSeconds();
}
