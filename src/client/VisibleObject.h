#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "consts.h"

class VisibleObject
{
protected:
    sf::Vector2f position;

public:

    VisibleObject(sf::Vector2f pos) : position(pos){}

    virtual void render(sf::RenderWindow&) = 0;

    virtual bool update(){return 1;}

    sf::Vector2f getPosition() const {return position;}

    virtual ~VisibleObject() {}

};