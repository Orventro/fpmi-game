#pragma once

#include "consts.h"
#include "Unit.h"
#include "World.h"
#include <vector>
#include <set>
#include <deque>

class Army
{

private:
    set<Unit*> units;
    Unit* selected = 0;
    World* home;
    bool active = 0;
    bool animation = 0;
    const int id;
    int gold = START_GOLD;
    std::deque<sf::Vector2f> path;

    sf::CircleShape attackRad, moveRad;

public:
    Army(World* world, int id); // id in [0, 4)

    void render(sf::RenderWindow& window);
    void update(float delta);
    void newMove();
    void endMove();
    bool recruit(sf::Vector2f point, int unitType);
    bool select(sf::Vector2f point);
    bool unselect();
    bool isAnimating() const;
    void giveGold(int);
    int getGold() const;
    void attack(Unit* u);
    void moveTo(std::deque<sf::Vector2f> path, float newEnergy);
    Unit* getSelectedUnit() const;
    int getId();
    const set<Unit*>* getUnits() const;

    ~Army();

};