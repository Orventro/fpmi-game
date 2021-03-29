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
    sf::Text gold_amount;
    sf::Font gold_font;
    sf::Vector2f size;

public:

    World(sf::Vector2f _size = windowDims * 2.0f);

    void render(sf::RenderWindow& window, float delta, bool active);

    void passEvent(sf::Event event, sf::RenderWindow& window);

    const vector<Army*>& getArmies() const;

    ~World();
};
