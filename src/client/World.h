#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <set>
#include "VisibleObject.h"
#include "Army.h"
#include "consts.h"
#include "maker_map.h"
#include "Window.h"

class GameWindow;

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
    GameWindow* const gameWindow;

    void update_town ();

public:

    World(GameWindow *_window, sf::Vector2f _size = WORLD_SIZE);

    void render(sf::RenderWindow& window, float delta, bool active);
    void passEvent(sf::Event event, sf::RenderWindow& window);
    const vector<Army*>& getArmies() const;
    void onResized();

    ~World();
};
