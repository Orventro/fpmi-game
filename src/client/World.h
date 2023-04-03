#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <set>
#include "WorldMap.h"
#include "consts.h"
#include "VisibleObject.h"
#include "Army.h"
#include "Window.h"

class World
{
private:
    sf::Vector2f size, windowSize;
    vector<Army *> armies;
    Army *activeArmy;
    sf::View camera;
    WorldMap *map;
    int turn = 0;

    void update_town();
    void moveCamera(sf::RenderWindow &renderWindow, float delta);

public:
    World(sf::Vector2f winSize = DEFAULT_WINDOW_SIZE, sf::Vector2f _size = WORLD_SIZE);

    // returns 1 if game not ended yet, otherwise 0
    int render(sf::RenderWindow &window, float delta, bool drawTownRadius, bool drawMovementBorder);

    // adapt to new window size
    void onResized(sf::Vector2f);

    // return closest unprotected town to point
    Town *seizeTown(sf::Vector2f point);

    // select unit at point
    bool selectUnit(sf::Vector2f point);

    // select unit with id
    bool selectUnit(int id);

    // tell selected unit to do something at point
    bool action(sf::Vector2f point);

    // change active army
    void newMove();

    // unselect unit
    bool unselect();

    // recruit new unit of unitType for active army at point
    bool recruit(sf::Vector2f point, int unitType);

    // get active army gold
    int getAAGold() const;

    // get active army id
    int getAAId() const;

    // transform point to absolute coords
    void transformPoint(sf::Vector2f &point) const;

    Unit *getSelected() const;

    ~World();
};
