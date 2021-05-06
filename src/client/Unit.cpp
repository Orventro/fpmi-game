#include "Unit.h"

Unit::Unit(sf::Vector2f _position, unsigned int type ,float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color) :
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
    flag_attack = true;
    switch ( type )
    {
    case 1: shape.setPointCount(4); break;
    case 2: shape.setPointCount(3); break;
    case 3: shape.setPointCount(6); break;
    case 4: shape.setPointCount(32); break;
    }
    shape.setFillColor(color);
    shape.setOrigin(20, 20);
    shape.setRotation(90);
}

void Unit::newMove()
{
    energy = maxEnergy;
    flag_attack = false;
}

void Unit::moveTo(std::deque<sf::Vector2f> _path, float newEnergy)
{
    path = _path;
    energy = newEnergy;
}

float Unit::getAtkRad() const
{
    return attackRadius;
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
    if( flag_attack ) 
        return 0;
    if(norm(u->getPosition() - position) <= attackRadius*attackRadius) {
        u->attacked(damage);
        flag_attack = true;
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

bool Unit::canAttack() const
{
    return !flag_attack;
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