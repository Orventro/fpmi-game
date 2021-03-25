#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <set>
#include "VisibleObject.h"
#include "Army.h"
#include "consts.h"
#include "maker_map.h"

class World{
private:
    set<VisibleObject*> objects;
    vector<Army*> armies;
    Army* activeArmy;
    sf::View camera;
    maker_map map;
    int turn = 0;
public:

    World();

    void render(sf::RenderWindow& window, bool active);

    void update(float delta);

    void passEvent(sf::Event event, sf::RenderWindow& window);

    ~World();
};
