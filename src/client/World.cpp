#include "World.h"
#include "consts.h"

World::World()
{
    mainPlayer = new Player();

    mt19937 gen(0);
    for(int i = 0; i < 20; i++) {
        float x = gen() % 2000 - 1000, y = gen() % 2000 - 1000;
        objects.insert(new Rock({x, y}));
    }
}

void World::passEvent(sf::Event event)
{

}

void World::render(sf::RenderWindow& window, sf::Vector2f cameraPosition)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        mainPlayer->accelerate(PLAYER_ACCELERATION*UP);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mainPlayer->accelerate(PLAYER_ACCELERATION*LEFT);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        mainPlayer->accelerate(PLAYER_ACCELERATION*DOWN);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mainPlayer->accelerate(PLAYER_ACCELERATION*RIGHT);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        Bullet* b;
        if(b = mainPlayer->shoot()) 
            objects.insert(b);
    }

    sf::Vector2f mouse_pos(sf::Mouse::getPosition(window));
    mainPlayer->rotate_to(sf::Vector2f(mouse_pos + cameraPosition - windowDims * 0.5f));

    vector<VisibleObject*> to_erase;
    for(auto o : objects) {
        if(!o->render(window))
            to_erase.push_back(o);
    }
    for(auto o : to_erase) {
        delete o;
        objects.erase(o);
    }



    mainPlayer->render(window);
}

sf::Vector2f World::getMCposition()
{
    return mainPlayer->getPosition();
}