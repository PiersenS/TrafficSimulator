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
    sf::Texture texture;

    static sf::Texture randomCar();

public:
    Car();
    Car(sf::Texture texture, sf::Vector2f pos, float dir);
    void setScaleFactor(float factor);
    sf::Vector2f getPosition();
    float getSpeed();
};
#endif