#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Resources.h"
#include "Army.h"
#include "consts.h"

class Town : public VisibleObject
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    Army *owner; // 0 - none

public:
    Town(const sf::Vector2f pos = sf::Vector2f(0, 0), Army *player = 0);
    ~Town();
    Army *get_owner() const;
    void setOwner(Army *pl);
    void render(sf::RenderWindow &window);
    bool isProtected() const;
};
