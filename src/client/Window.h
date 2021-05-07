#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <tuple>
#include <cstdio>
#include "VisibleObject.h"
#include "World.h"
#include "Client.h"

class GameWindow
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool inFocus = 0;
    World *world;
    Client client;

    int type_of_new_unit;
    int myArmyId = 1;

    // UI
    sf::Text hint, goldAmount;
    sf::Font defaultFont, goldFont;
    sf::CircleShape townRad;

    enum state_ids
    {
        STATE_NEUTRAL,
        STATE_WAITING,
        STATE_CHOOSING,
        STATE_PLACING,
        STATE_SELECTED,
        STATE_FINISH
    };
    std::string hints[6]{
        "Press N to buy new units or click on your unit to select it",
        "Waiting for opponent to make their move",
        "Press number key to choose new unit type: ",
        "Click near seized town to place your new unit",
        "Click to move or attack",
        "Game Ended"};
    // these functions are for finite automaton

    void neutral(sf::Event);         // default state: unit not selected
    void waiting(sf::Event);         // awaiting for your move
    void choose_new_unit(sf::Event); // choosing new unit
    void place_new_unit(sf::Event);  // placing new unit
    void unit_selected(sf::Event);   // unit selected, waiting for command to it
    void finish(sf::Event);          // end game

    void send(ACTION actionType, int num = 0, sf::Vector2f vec = sf::Vector2f(0, 0));

    void (GameWindow::*states[6])(sf::Event) = {
        &GameWindow::neutral,
        &GameWindow::waiting,
        &GameWindow::choose_new_unit,
        &GameWindow::place_new_unit,
        &GameWindow::unit_selected,
        &GameWindow::finish};

    void setState(int state_id);

    void (GameWindow::*state)(sf::Event);
    // std::function<void(sf::Event)> state;

public:
    GameWindow(sf::Vector2f size = DEFAULT_WINDOW_SIZE);

    // returns 0 if everything is ok, 1 if error or was ordered to close
    int render();

    ~GameWindow();
};