#pragma once

#include <complex>
#include <cmath>
#include <chrono>
#include "VisibleObject.h"
#include "Bullet.h"
#include "consts.h"

using namespace std;

class Player : public VisibleObject
{
private:
    sf::Vector2f position, origin, velocity;
    float targetAngle, health;
    sf::CircleShape traingle;
    timestamp lastShot;
    

public:
    Player(sf::Vector2f _position = sf::Vector2f(0,0));
        
    void accelerate(sf::Vector2f acceleration);

    void rotate_to(sf::Vector2f target);

    virtual bool render(sf::RenderWindow &window);

    sf::Vector2f getPosition();

    Bullet* shoot();
};

