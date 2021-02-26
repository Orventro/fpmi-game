#include "Rock.h"

Rock::Rock(sf::Vector2f _position) :
    position(_position),
    shape(40, 4)
{
    shape.setPosition(position);
}

bool Rock::render(sf::RenderWindow& window)
{
    window.draw(shape);
    return 1;
}