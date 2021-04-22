#pragma once

#include "consts.h"
#include "VisibleObject.h"
#include "Bar.h"

class Unit : public VisibleObject 
{
private:
    bool alive = 1;
    float energy;
    float health, maxHealth, speed, damage, maxEnergy, attackRadius;
    sf::CircleShape shape;
    Bar hpbar;

public:
    sf::Vector2f destination;
    Unit(sf::Vector2f _position, float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color);

    void newMove();
    bool moveTo(sf::Vector2f point);
    bool attack(Unit* u);
    void attacked(float dmg);
    void render(sf::RenderWindow& window);
    bool update(float delta);
    bool isAnimating() const;
    void finishAnimation();
    float getEnergy() const;

    ~Unit();
};