#include "Bar.h"

Bar::Bar(sf::Vector2f _position, sf::Vector2f size, sf::Color frontCol, sf::Color backCol) :
    VisibleObject(_position),
    front(size),
    back(size)
{
    front.setFillColor(frontCol);
    back.setFillColor(backCol);
    front.setOrigin(size / 2.0f);
    back.setOrigin(size / 2.0f);
}

void Bar::setProgress(float progress)
{
    sf::Vector2f size = back.getSize();
    front.setSize({size.x * progress, size.y});
    front.setPosition(position - sf::Vector2f(size.x * (1-progress), 0));
}

void Bar::moveTo(sf::Vector2f _position)
{
    position = _position;
    back.setPosition(position);
    front.setPosition(position + front.getSize() - back.getSize()); // y cancels out
}

void Bar::render(sf::RenderWindow& window)
{
    window.draw(back);
    window.draw(front);
}