#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <set>
#include "VisibleObject.h"
#include "Player.h"
#include "Rock.h"

class World{
    Player *mainPlayer;
    vector<Player*> players;
    set<VisibleObject*> objects;

public:

    World();

    void passEvent(sf::Event event);

    void render(sf::RenderWindow& window, sf::Vector2f cameraPosition);

    sf::Vector2f getMCposition();
};
