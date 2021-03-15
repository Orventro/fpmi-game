#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <set>
#include "VisibleObject.h"
#include "Army.h"

class World{
private:
    // Player *mainPlayer;
    // vector<Player*> players;
    set<VisibleObject*> objects;
    vector<Army*> armies;
    int turn;
    sf::Vector2f cameraPosition;

public:

    World();

    void render(sf::RenderWindow& window);

    void update(float delta, sf::Vector2f _cameraPosition);

    void passEvent(sf::Event event, sf::RenderWindow& window);

    ~World();
};
