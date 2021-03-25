#pragma once

#include <SFML/Graphics.hpp>
#include "VisibleObject.h"
#include "World.h"

using namespace std;

class GameWindow
{
private:
    sf::RenderWindow window;
    sf::CircleShape shape;
    sf::Clock clock;
    bool inFocus = 0;

    World* world;

public:
    GameWindow(sf::Vector2f size = sf::Vector2f(1080, 720));

    int render();

    ~GameWindow();
};