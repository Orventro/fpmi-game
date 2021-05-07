#include "World.h"
#include "consts.h"

World::World(sf::Vector2f winSize, sf::Vector2f _size) : size(_size),
                                                         camera(sf::FloatRect(0, 0, winSize.x, winSize.y))
{
    map = new WorldMap(_size.y, _size.x, 100, 100, 1);
    map->render();
    const int armiesNum = 2;
    // armies.push_back(new Army(0, map->start_coord.first));
    // armies.push_back(new Army(1, map->start_coord.second));
    Town *t;
    do
    {
        t = map->getRandTown();
        if (t->get_owner() == 0)
        {
            armies.push_back(new Army(armies.size(), t->getPosition()));
            t->setOwner(armies.back());
        }
    } while (armies.size() < armiesNum);

    activeArmy = armies[0];
    activeArmy->newMove();
    activeArmy->giveGold(10); // for first town
    camera.setCenter(size.x / 2, size.y / 2);
}

void World::newMove()
{
    activeArmy->endMove();
    activeArmy = armies[(++turn) % armies.size()];
    activeArmy->newMove();

    for (Town *t : map->getTowns())
        if (t->get_owner() == activeArmy)
            activeArmy->giveGold(10);
}

bool World::selectUnit(sf::Vector2f point)
{
    if (activeArmy->select(point))
    {
        // cout << "rb\n";
        map->renderBorder(sf::Vector2u(activeArmy->getSelectedUnit()->getPosition()), activeArmy->getSelectedUnit()->getEnergy());
        return 1;
    }
    return 0;
}

bool World::selectUnit(int id)
{
    return activeArmy->select(id);
}

bool World::action(sf::Vector2f point)
{

    float normToUnit = 400; // max norm to detect click
    Unit *pointedUnit = 0;
    for (auto a : armies)
    {
        if (a == activeArmy)
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
    if (pointedUnit)
        return activeArmy->attack(pointedUnit);
    else
    {
        auto path = map->getPath(point);
        if (path.second != 0)
        {
            activeArmy->moveTo(path.first, path.second);
            Town *t = seizeTown(point);
            if (t)
                t->setOwner(activeArmy);
            map->renderBorder(sf::Vector2u(point), path.second);
            return 1;
        }
    }
    return 0;
}

bool World::unselect()
{
    return activeArmy->unselect();
}

int World::getAAGold() const
{
    return activeArmy->getGold();
}

// formula for camera movement
float move_speed(float x, float range)
{
    if (x >= 0)
        return std::max(1.0f / (x / range * 5 + 2.5f) - 0.3f, 0.0f) * 20 * range;
    else
        return 0;
}

void World::moveCamera(sf::RenderWindow &renderWindow, float dt)
{
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

void World::render(sf::RenderWindow &renderWindow, float dt, bool drawTownRadius, bool drawMovementBorder)
{
    for (Army *a : armies)
        a->update(dt);

    moveCamera(renderWindow, dt);

    map->draw(renderWindow, drawTownRadius, drawMovementBorder);

    for (auto a : armies)
        a->render(renderWindow);

    // gold_amount.setOrigin(-camera.getCenter() + sf::Vector2f(windowSize) * 0.5f + GOLD_OFFSET);
    // renderWindow.draw(gold_amount);
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
    // проверяем, если рядом с выбранной точкой есть город, принадлежащий этой армии
    for (Town *t : map->getTowns())
        if ((norm(t->getPosition() - point) < TOWN_RADIUS2) & (t->get_owner() == activeArmy))
            return activeArmy->recruit(point, unitType);
    return 0;
}

int World::getAAId() const
{
    return activeArmy->getId();
}

void World::transformPoint(sf::Vector2f &point) const
{
    point += camera.getCenter() - windowSize * 0.5f;
}

Unit *World::getSelected() const
{
    return activeArmy->getSelectedUnit();
}

World::~World()
{
    for (auto a : armies)
        delete a;
    delete map;
}

Town *World::seizeTown(sf::Vector2f point)
{
    for (Town *t : map->getTowns())
        if (norm(t->getPosition() - point) < TOWN_RADIUS2 && !t->isProtected())
            return t;
    return 0;
}
