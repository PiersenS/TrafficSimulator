/* C++ includes */
#include <random>
#include <cmath>
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
    if (length != 0) {
        return sf::Vector2f(source.x / length, source.y / length); // normalized vector
    }
    return source;
}