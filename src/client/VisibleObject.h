#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class VisibleObject
{

public:

    virtual bool render(sf::RenderWindow& window){return 1;}

    virtual void update(){}
};