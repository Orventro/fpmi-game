#pragma once

#include <SFML/Graphics.hpp>
#include "VisibleObject.h"
#include "World.h"

using namespace std;

class GameWindow: public VisibleObject
{
private:
    sf::RenderWindow window;
    sf::CircleShape shape;
    sf::View camera;

    World* world;

public:
    GameWindow(sf::Vector2f size = sf::Vector2f(1080, 720));

    int render();
};