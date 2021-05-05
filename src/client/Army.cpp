#include "Army.h"

Army::Army(int _id, sf::Vector2f start) :
    attackRad(50, 32),
    moveRad(500, 32),
    id(_id)
{           
    units.insert(new Unit(  start , 1  , ARMY_COLORS[id] ));
    moveRad.setFillColor(MOVE_COLOR);
    attackRad.setFillColor(ATTACK_COLOR);
    attackRad.setOrigin(50, 50);
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
    for(Unit* u : units) 
        u->render(window);
    
    // if(selected) {
    //     moveRad.setRadius(selected->getEnergy());
    //     moveRad.setOrigin(selected->getEnergy(), selected->getEnergy());
    //     moveRad.setPosition(selected->getPosition());
    //     window.draw(moveRad);

    //     if(selected->getEnergy() >= 400) {
    //         window.draw(attackRad);
    //         attackRad.setPosition(selected->getPosition());
    //     }
    // }
}

void Army::newMove()
{
    if(selected)
        selected->finishAnimation();
    active = 1;
    // gold += 10;
    for(Unit* u : units)
        u->newMove();
    
    // cout << id << " new move\n";
}

void Army::endMove()
{
    active = 0;
    selected = 0;
    // cout << id << " end move\n";
}

bool Army::recruit(sf::Vector2f point, int unitType) 
{
    switch ( unitType )
    {
    case 1:
        if(gold >= Price_unit[0] ){
            gold -= Price_unit[0];
            units.insert(new Unit(point, 1,  ARMY_COLORS[id]));
            return 1;
        }
        else
            return 0;
        break;                          
    case 2:
        if(gold >=  Price_unit[1] ){
            gold -= Price_unit[1];
            units.insert(new Unit(point, 2 ,  ARMY_COLORS[id]));
            return 1;
        }
        else
            return 0;
        break; 
    case 3:
        if(gold >= Price_unit[2]){
            gold -= Price_unit[2];
            units.insert(new Unit(point, 3, ARMY_COLORS[id]));
            return 1;
        }
        else
            return 0;
        break;
    case 4:
        if(gold >= Price_unit[3]){
            gold -= Price_unit[3];
            units.insert(new Unit(point, 4, ARMY_COLORS[id]));
            return 1;
        }
        else
            return 0;
        break;
    
    default:
        return 0;
        break;
    }

    return 0;
}

void Army::attack(Unit* u)
{
    if(selected) selected->attack(u);
}

void Army::moveTo(std::deque<sf::Vector2f> _path, float newEnergy)
{
    if(selected)
        selected->moveTo(_path, newEnergy);
}

Unit* Army::getSelectedUnit() const 
{
    return selected;
}

bool Army::select(sf::Vector2f point) 
{
    if(isAnimating())
        return 0;
    // cout << point << (*units.begin())->getPosition() << endl;
    float normToUnit = 400; // max dist to detect click
    Unit *pointedUnit = 0;
    for (auto u : units)
    {
        if (normToUnit > norm(u->getPosition() - point))
        {
            normToUnit = normToUnit;
            pointedUnit = u;
        }
    }
    if(pointedUnit == 0)
        return 0;
    selected = pointedUnit;
    return 1;
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

bool Army::unselect()
{
    if(!selected)
        return 1;
    if(selected->isAnimating())
        return 0;
    selected = 0;
    return 1;
}

int Army::getGold() const
{
    return gold;
}

void Army::giveGold(int amount)
{
    gold += amount;
}

int Army::getId()
{
    return id;
}

Army::~Army()
{
    for(auto u : units)
        delete u;
}