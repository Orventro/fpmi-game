#include "World.h"
#include "consts.h"

World::World(sf::Vector2f winSize, sf::Vector2f _size) :
                            size(_size),
                            camera(sf::FloatRect(0, 0, winSize.x, winSize.y))
{
    map = new WorldMap(_size.y, _size.x, 100, 100, size_elemantary_block_in_pixel * pixel_size, 1);
    armies.push_back(new Army(this, 0));
    armies.push_back(new Army(this, 1));
    activeArmy = armies[0];
    activeArmy->newMove();
    map->render();
    camera.setCenter(size.x / 2, size.y / 2);
}

void World::newMove()
{   
    activeArmy->endMove();
    activeArmy = armies[(++turn) % armies.size()];
    activeArmy->newMove();

    for(Town *t : map->getTowns())
        if(t->get_owner() == activeArmy)
            activeArmy->giveGold(10);
}

bool World::selectUnit(sf::Vector2f point) {
    point += camera.getCenter() - windowSize*0.5f;
    return activeArmy->select(point);
}

void World::action(sf::Vector2f point) {
    // Calculate click target
    point += camera.getCenter() - windowSize*0.5f;

    float normToUnit = 400; // max dist to detect click
    Unit *pointedUnit = 0;
    for (auto a : armies)
    {
        if(a == activeArmy)
            continue;
        for (auto u : *a->getUnits())
        {
            if (normToUnit > norm(u->getPosition() - point))
            {
                normToUnit = normToUnit;
                pointedUnit = u;
            }
        }
    }
    activeArmy->action(pointedUnit, point);
}

bool World::unselect()
{
    return activeArmy->unselect();
}

int World::getGold(){
    return activeArmy->getGold();
}

float move_speed(float x, float range)
{
    if (x >= 0)
        return std::max(1.0f / (x / range * 5 + 2.5f) - 0.3f, 0.0f) * 20 * range;
    else
        return 0;
}

void World::moveCamera(sf::RenderWindow& renderWindow, float dt){
    int x = sf::Mouse::getPosition(renderWindow).x;
    int y = sf::Mouse::getPosition(renderWindow).y;
    float adjDelta = std::min(dt, 1.0f);

    float winWidth = windowSize.x,
            winHeight = windowSize.y;

    // moving camera
    camera.move(move_speed(x, winWidth) * LEFT * adjDelta);
    camera.move(move_speed(winWidth - x, winWidth) * RIGHT * adjDelta);
    camera.move(move_speed(y, winHeight) * UP * adjDelta);
    camera.move(move_speed(winHeight - y, winHeight) * DOWN * adjDelta);

    // no escaping out of the world
    if (camera.getCenter().x - winWidth / 2 <= 0)
        camera.setCenter({winWidth / 2, camera.getCenter().y});
    if (camera.getCenter().x - size.x + winWidth / 2 >= 0)
        camera.setCenter({size.x - winWidth / 2, camera.getCenter().y});
    if (camera.getCenter().y - winHeight / 2 <= 0)
        camera.setCenter({camera.getCenter().x, winHeight / 2});
    if (camera.getCenter().y - size.y + winHeight / 2 >= 0)
        camera.setCenter({camera.getCenter().x, size.y - winHeight / 2});

    renderWindow.setView(camera);

}

void World::render(sf::RenderWindow &renderWindow, float dt, bool drawTownRadius)
{
    for (Army *a : armies)
        a->update(dt);

    moveCamera(renderWindow, dt);
    
    map->draw(renderWindow, {0, 0}, drawTownRadius);

    for (auto o : objects)
        o->render(renderWindow);

    for (auto a : armies)
        a->render(renderWindow);

    // gold_amount.setOrigin(-camera.getCenter() + sf::Vector2f(windowSize) * 0.5f + GOLD_OFFSET); 
    // renderWindow.draw(gold_amount);
}

const vector<Army *> &World::getArmies() const
{
    return armies;
}

void World::onResized(sf::Vector2f winSize)
{
    windowSize = winSize;
    sf::Vector2f center = camera.getCenter();
    camera = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    camera.setCenter(center);
}

bool World::recruit(sf::Vector2f point, int unitType)
{
    point += camera.getCenter() - windowSize*0.5f;
    
    // проверяем, если рядом с выбранной точкой есть город, принадлежащий этой армии
    for(Town *t : map->getTowns()) {
        if(norm(t->getPosition() - point) < TOWN_RADIUS2 & t->get_owner() == activeArmy) {
            if (activeArmy->recruit(point, unitType))
                return 1;
            else cout << "no recr\n";
        }
    }
    return 0;
}

World::~World()
{
    for (auto a : armies)
    {
        delete a;
    }
}

Town* World::seizeTown(sf::Vector2f point){
    for(Town* t : map->getTowns()) 
        if(norm(t->getPosition() - point) < TOWN_RADIUS2 && !t->isProtected())
            return t;
    return 0;
}
