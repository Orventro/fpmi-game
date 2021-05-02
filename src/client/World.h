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

class World{
private:
    sf::Vector2f size, windowSize;
    vector<Army*> armies;
    Army* activeArmy;
    sf::View camera;
    WorldMap* map;
    int turn = 0;

    void update_town ();
    void moveCamera(sf::RenderWindow& renderWindow, float delta);

public:

    World(sf::Vector2f winSize = DEFAULT_WINDOW_SIZE, sf::Vector2f _size = WORLD_SIZE);

    void render(sf::RenderWindow& window, float delta, bool drawTownRadius, bool drawMovementBorder);
    void updateWindowSize(sf::Vector2f);
    const vector<Army*>& getArmies() const;
    void onResized(sf::Vector2f);
    Town* seizeTown(sf::Vector2f);
    bool selectUnit(sf::Vector2f);
    void action(sf::Vector2f);
    void newMove();
    bool unselect();
    bool recruit(sf::Vector2f point, int unitType);
    int getGold();
    
    ~World();
};
