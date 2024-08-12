#ifndef Car_H
#define Car_H

#include <SFML/Graphics.hpp>

class Car : sf::Sprite {
private:
    sf::Texture texture;
    // car textures - all but red
    // roygbiv
    static const std::string textures[6]; // {"pink", "orange", "green", "teal", "blue", "purple"};

public:
    Car();
    Car(sf::Texture t);
    void setTexture(sf::Texture t);
    sf::Texture getTexture();
};
#endif