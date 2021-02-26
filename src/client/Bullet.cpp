#include "Bullet.h"

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _velocity, float _angle) :
    position(_position),
    velocity(_velocity),
    angle(_angle),
    shape({30.0f, 6.0f})
{
    shape.setOrigin(15.f, 3.f);
    shape.setRotation(angle);
    shape.setPosition(position);
}

bool Bullet::render(sf::RenderWindow &window){
    position += velocity;

    if(position.x*position.x + position.y*position.y > 1e7)
        return 0;

    shape.setPosition(position);
    window.draw(shape);
    return 1;
}