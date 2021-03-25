#pragma once

#include "consts.h"
#include "VisibleObject.h"

class Bar : public VisibleObject
{
private:
    sf::RectangleShape back;
    sf::RectangleShape front;

public:
    Bar(sf::Vector2f position, sf::Vector2f size, sf::Color backCol, sf::Color frontCol);

    void setProgress(float progress);

    virtual void render(sf::RenderWindow& window);

    void moveTo(sf::Vector2f _posiiton);

};