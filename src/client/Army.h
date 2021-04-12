#pragma once

#include "consts.h"
#include "Unit.h"
#include <vector>
#include <set>


class Army
{

private:
    set<Unit*> units;
    Unit* selected = 0;
    bool active = 0;
    bool animation = 0;
    const int id;
    sf::CircleShape selectIndicator, attackRad, moveRad;
    int gold = START_GOLD;


public:
    Army(int id); // id in [0, 4)

    void render(sf::RenderWindow& window);
    void update(float delta);
    void newMove();
    void endMove();
    void recruit();
    void action(Unit* u, sf::Vector2f point, sf::Mouse::Button button);
    bool isAnimating() const;
    int getGold() const;
    const set<Unit*>* getUnits() const;

    ~Army();

};