#pragma once

#include "VisibleObject.h"

class Bullet : public VisibleObject
{
private:
    sf::RectangleShape shape;
    sf::Vector2f position, velocity;
    float angle;

public:
    Bullet(sf::Vector2f _position, sf::Vector2f _velocity, float _angle);

    bool render(sf::RenderWindow &window);
};