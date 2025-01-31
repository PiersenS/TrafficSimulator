#ifndef TS_UTILS_H
#define TS_UTILS_H

#include <SFML/Graphics.hpp>

namespace ts {
    static int random(int min, int max);
    static sf::Vector2f normalize(sf::Vector2f v);
}

#endif