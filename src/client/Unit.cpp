#include "Unit.h"

Unit::Unit(sf::Vector2f _position, float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color) :
    VisibleObject(_position),
    health(_health),
    maxHealth(_health),
    speed(_speed),
    damage(_damage),
    maxEnergy(_maxEnergy),
    attackRadius(_attackRadius),
    shape(20, 4),
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

void Unit::moveTo(std::deque<sf::Vector2f> _path, float newEnergy)
{
    path = _path;
    energy = newEnergy;
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
    if(energy < 400) // 400 - cost of attack (for now)
        return 0;
    if(norm(u->getPosition() - position) <= attackRadius*attackRadius) {
        u->attacked(damage);
        energy -= 400;
        return 1;
    }
    return 0;
}

bool Unit::update(float dt)
{ 
    if(path.size() == 0)
        return alive;

    float dl = dt*speed;

    float ds = vlen(path.back() - position);

    while(dl >= ds)
    {
        dl -= ds;
        position = path.back();
        path.pop_back();
        if(path.size() == 0)
            break;
        ds = vlen(path.back() - position);
    }

    if(path.size())
        position = position * (1 - dl/ds) + path.back() * dl/ds;
    
    hpbar.moveTo(position + HP_BAR_OFFSET);

    return alive;
}

void Unit::finishAnimation(){
    position = path.back();
}

void Unit::render(sf::RenderWindow& window)
{   
    shape.setPosition(position);
    window.draw(shape);
    hpbar.render(window);
}

bool Unit::isAnimating() const
{
    return path.size();
}

float Unit::getEnergy() const
{
    return energy;
}