#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "VisibleObject.h"
#include "World.h"

class GameWindow
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool inFocus = 0;
    World* world;

    // UI
    sf::Text hint, goldAmount;
    sf::Font defaultFont, goldFont;
    sf::CircleShape townRad;
    // int myArmyId = 0;

    // these functions are for finite automaton
    void neutral(sf::Event); // default state: unit not selected
    void waiting(sf::Event); // awaiting for your move (currently not used)
    void choose_new_unit(sf::Event); // choosing new unit
    void place_new_unit(sf::Event); // placing new unit
    void unit_selected(sf::Event); // unit selected, waiting for command to it

    void (GameWindow::*state)(sf::Event);
    // std::function<void(sf::Event)> state;

public:
    GameWindow(sf::Vector2f size = DEFAULT_WINDOW_SIZE);

    int render();

    ~GameWindow();
};