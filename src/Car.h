#ifndef Car_H
#define Car_H

#include <SFML/Graphics.hpp>

class Car : public sf::Sprite {
private:
    static const std::string textures[6];
    float speed;
    float direction; // angle of rotation
    float scaleFactor;
    sf::Vector2f position;

    static sf::Texture& randomCar();

public:
    Car(sf::Texture& texture = randomCar(), sf::Vector2f pos = sf::Vector2f(565, 64), float dir = 0.0f);
    void setScaleFactor(float factor);
    sf::Vector2f getPosition();
    float getSpeed();
};
#endif