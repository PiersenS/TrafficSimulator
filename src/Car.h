#ifndef Car_H
#define Car_H

#include <SFML/Graphics.hpp>

class Car {
private:
    sf::Texture texture;
    // car textures - all but red
    // roygbiv
    static const std::string textures[6]; // {"pink", "orange", "green", "teal", "blue", "purple"};

public:
    Car();
    Car(Texture t);
    void setTexture(Texture t);
    sf::Texture getTexture();
};
#endif