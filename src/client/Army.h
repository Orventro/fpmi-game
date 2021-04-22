#pragma once

#include "consts.h"
#include "Unit.h"
#include "World.h"
#include <vector>
#include <set>

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
    sf::CircleShape attackRad, moveRad;

public:
    Army(World* world, int id); // id in [0, 4)

    void render(sf::RenderWindow& window);
    void update(float delta);
    void newMove();
    void endMove();
    bool recruit(sf::Vector2f point, int unitType);
    void action(Unit* u, sf::Vector2f point);
    bool select(sf::Vector2f point);
    bool unselect();
    bool isAnimating() const;
    void giveGold(int);
    int getGold() const;
    int getId();
    const set<Unit*>* getUnits() const;

    ~Army();

};