#include "Bar.h"

Bar::Bar(sf::Vector2f _position, sf::Vector2f size, sf::Color frontCol, sf::Color backCol) : VisibleObject(_position),
                                                                                             back(size),
                                                                                             front(size)

{
    front.setFillColor(frontCol);
    back.setFillColor(backCol);
    front.setOrigin(size / 2.0f);
    back.setOrigin(size / 2.0f);
    front.setPosition(position);
    back.setPosition(position);
}

void Bar::setProgress(float progress)
{
    sf::Vector2f size = back.getSize();
    front.setSize({size.x * progress, size.y});
}

void Bar::moveTo(sf::Vector2f _position)
{
    position = _position;
    back.setPosition(position);
    front.setPosition(position);
}

void Bar::render(sf::RenderWindow &window)
{
    window.draw(back);
    window.draw(front);
}