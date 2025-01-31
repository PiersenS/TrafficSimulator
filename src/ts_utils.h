#ifndef TS_UTILS_H
#define TS_UTILS_H

#include <SFML/Graphics.hpp>

namespace ts {
    int random(int min, int max);
    sf::Vector2f normalize(sf::Vector2f source);
}

#endif