#include "Unit.h"

Unit::Unit(sf::Vector2f _position, float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color) :
    VisibleObject(_position),
    destination(_position),
    health(_health),
    maxHealth(_health),
    speed(_speed),
    damage(_damage),
    maxEnergy(_maxEnergy),
    shape(20, 4),
    attackRadius(_attackRadius),
    hpbar(_position + HP_BAR_OFFSET, HP_BAR_SIZE, HP_BACK_COL, HP_FRONT_COL)
{
    shape.setFillColor(color);
    shape.setOrigin(20, 20);
    shape.setRotation(90);
}

void Unit::newMove()
{
    energy = maxEnergy;
}

bool Unit::moveTo(sf::Vector2f point)
{
    if(norm(point - position) <= energy*energy) {
        destination = point;
        energy -= sqrt(norm(point - position));
        return 1;
    }
    return 0;
}

void Unit::attacked(float dmg) {
    health = std::max(0.0f, health - dmg);
    if(health == 0.0f) {
        alive = 0;
    }
    hpbar.setProgress(health / maxHealth);
}

bool Unit::attack(Unit* u)
{
    if(norm(u->getPosition() - position) <= attackRadius*attackRadius) {
        u->attacked(damage);
        return 1;
    }
    return 0;
}

bool Unit::update(float delta)
{
    if(destination == position)
        return alive;
    
    if(delta*delta*speed*speed >= norm(destination - position)) {
        position = destination;
    } else {
        float ratio = delta*speed/sqrt(norm(destination - position));
        position = position * (1 - ratio) + destination * ratio;
    }

    hpbar.moveTo(position + HP_BAR_OFFSET);

    return alive;
}

void Unit::render(sf::RenderWindow& window)
{   
    shape.setPosition(position);
    window.draw(shape);
    hpbar.render(window);
}

bool Unit::isAnimating() const
{
    return destination != position;
}

float Unit::getEnergy() const
{
    return energy;
}

Unit::~Unit()
{
}