#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "VisibleObject.h"
#include "World.h"

class GameWindow
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool inFocus = 0;
    World* world;

    int current_type_unit;

    // UI
    sf::Text hint, goldAmount;
    sf::Font defaultFont, goldFont;
    sf::CircleShape townRad;
    // int myArmyId = 0;

    enum state_ids {STATE_NEUTRAL, STATE_WAITING, STATE_CHOOSING, STATE_PLACING, STATE_SELECTED};
    std::string hints[5] {
            "Press N to buy new units or click on your unit to select it",
            "",
            "Press number key to choose new unit type: ",
            "Click near seized town to place your new unit",
            "Click to move or attack"};
    // these functions are for finite automaton
    void neutral(sf::Event); // default state: unit not selected
    void waiting(sf::Event); // awaiting for your move (currently not used)
    void choose_new_unit(sf::Event); // choosing new unit
    void place_new_unit(sf::Event); // placing new unit
    void unit_selected(sf::Event); // unit selected, waiting for command to it

    void (GameWindow::*states[5])(sf::Event) = {
        &GameWindow::neutral, 
        &GameWindow::waiting, 
        &GameWindow::choose_new_unit, 
        &GameWindow::place_new_unit, 
        &GameWindow::unit_selected};

    void setState(int state_id);

    void (GameWindow::*state)(sf::Event);
    // std::function<void(sf::Event)> state;

public:
    GameWindow(sf::Vector2f size = DEFAULT_WINDOW_SIZE);

    int render();

    ~GameWindow();
};