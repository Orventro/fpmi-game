#pragma once

#include "VisibleObject.h"
#include "consts.h"

class Unit : public VisibleObject 
{
private:
    bool alive = 1;
    float energy;
    float health, speed, damage, maxEnergy, attackRadius;
    sf::Vector2f destination;
    sf::CircleShape shape;

public:
    Unit(sf::Vector2f _position, float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color);

    void newMove();
    bool moveTo(sf::Vector2f point);
    bool attack(Unit* u);
    void attacked(float dmg);
    void render(sf::RenderWindow& window);
    bool update(float delta);
    bool isAnimating() const;
    float getEnergy() const;

    ~Unit();
};