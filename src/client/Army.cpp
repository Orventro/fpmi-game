#include "Army.h"

Army::Army(int _id) :
    id(_id),
    selectIndicator(30, 16),
    attackRad(50, 32),
    moveRad(500, 64)
{
    selectIndicator.setFillColor(SELECT_COLOR);
    selectIndicator.setOrigin(30, 30);
    moveRad.setFillColor(MOVE_COLOR);
    attackRad.setFillColor(ATTACK_COLOR);
    attackRad.setOrigin(50, 50);
    units.insert(new Unit(ARMY_POSITIONS[id], 100, 300, 50, 500, 50, ARMY_COLORS[_id]));
}

void Army::update(float delta)
{
    vector<Unit*> dead;
    for(Unit* u : units) 
        if(!u->update(delta))
            dead.push_back(u);

    for(Unit* u : dead)
    {
        units.erase(u);
        delete u;
    }
}

void Army::render(sf::RenderWindow& window)
{    
    if(selected) {
        selectIndicator.setPosition(selected->getPosition());
        moveRad.setRadius(selected->getEnergy());
        moveRad.setOrigin(selected->getEnergy(), selected->getEnergy());
        moveRad.setPosition(selected->getPosition());
        attackRad.setPosition(selected->getPosition());

        
        window.draw(moveRad);
        window.draw(attackRad);
        window.draw(selectIndicator);
    }
    for(Unit* u : units) 
        u->render(window);
}

void Army::newMove()
{
    active = 1;
    for(Unit* u : units)
        u->newMove();
    
    cout << id << " new move\n";
}

void Army::endMove()
{
    active = 0;
    selected = 0;
    cout << id << " end move\n";
}

void Army::action(Unit* u, sf::Vector2f point, sf::Mouse::Button button)
{
    if(button == sf::Mouse::Button::Right) 
        if(selected != 0 && !selected->isAnimating())
            selected = 0;
    
    if(selected == 0)
    {
        if(u && units.count(u))
            selected = u;
    }
    else if(active)
    {
        if(u == 0) 
        {
            if(selected->moveTo(point)) 
                animation = 1;
        } 
        else
        {
            if(!units.count(u))
            {
                selected->attack(u);
            }
        }
        
    }
}

const set<Unit*>* Army::getUnits() const 
{
    return &units;
}

bool Army::isAnimating() const
{
    if(!selected)
        return 0;
    return selected->isAnimating();
}

Army::~Army()
{
    for(auto u : units)
        delete u;
}