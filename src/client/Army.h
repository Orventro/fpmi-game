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

public:
    Army(int id); // id in [0, 4)

    // void onClick(sf::Vector2f point);

    void render(sf::RenderWindow& window);

    void update(float delta);

    void newMove();

    void endMove();

    void action(Unit* u, sf::Vector2f point, sf::Mouse::Button button);

    const set<Unit*>* getUnits() const;

    bool isAnimating() const;

    ~Army();

};
