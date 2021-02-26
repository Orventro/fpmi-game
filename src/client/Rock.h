#pragma once

#include "VisibleObject.h"

using namespace std;

class Rock : public VisibleObject
{
private:
    // sf::Sprite sprite;
    sf::CircleShape shape;
    sf::Vector2f position;

public:
    Rock(sf::Vector2f _position);

    // bool intersects(sf::FloatRect box);

    bool render(sf::RenderWindow& window);
};
