#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "consts.h"

class VisibleObject
{
protected:
    sf::Vector2f position;

public:

    VisibleObject(sf::Vector2f _position) : position(_position){}

    virtual void render(sf::RenderWindow& window){}

    virtual bool update(float delta){return 1;}

    sf::Vector2f getPosition() const {return position;}

};