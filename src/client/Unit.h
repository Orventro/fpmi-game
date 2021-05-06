#pragma once

#include "consts.h"
#include "VisibleObject.h"
#include "Bar.h"
#include <deque>

class Unit : public VisibleObject 
{
private:
    bool alive = 1;
    bool flag_attack;
    float energy;
    float health, maxHealth, speed, damage, maxEnergy, attackRadius;
    sf::CircleShape shape;
    std::deque<sf::Vector2f> path;
    Bar hpbar;

public:
    Unit(sf::Vector2f _position,  unsigned int type ,float _health, float _speed, float _damage, float _maxEnergy, float _attackRadius, sf::Color color);

    void newMove();
    void moveTo(std::deque<sf::Vector2f> point, float newEnrgy);
    bool attack(Unit* u);
    void attacked(float dmg);
    void render(sf::RenderWindow& window);
    bool update(float delta);
    bool isAnimating() const;
    void finishAnimation();
    float getEnergy() const;
    bool canAttack() const;
    float getAtkRad() const;

};