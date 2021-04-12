#pragma once

#include <SFML/Graphics.hpp>
#include "VisibleObject.h"
#include "World.h"

using namespace std;

class World;

class GameWindow
{
private:
    sf::RenderWindow window;
    sf::CircleShape shape;
    sf::Clock clock;
    bool inFocus = 0;
    sf::Vector2u windowDims;

    World* world;

public:
    GameWindow(sf::Vector2u size = sf::Vector2u(800, 600));

    int render();

    sf::Vector2u getSize() const;

    ~GameWindow();
};