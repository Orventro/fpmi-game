#include "World.h"
#include "consts.h"

World::World() :
    turn(0)
{

    armies.push_back(new Army(0));
    armies.push_back(new Army(1));
    armies[0]->newMove();
}

void World::passEvent(sf::Event event, sf::RenderWindow& window)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        // Calculate click target

        sf::Vector2f mousePtr(sf::Mouse::getPosition(window));
        mousePtr += cameraPosition - windowDims * 0.5f;
        
        float normToUnit = 1e20;
        Unit* pointedUnit = 0;
        for(auto a : armies) 
        {
            
            for(auto u : *a->getUnits()) 
            {
                if(normToUnit > norm(u->getPosition() - mousePtr) ) 
                {
                    normToUnit = norm(u->getPosition() - mousePtr);

                    if(normToUnit < 400) 
                    {
                        pointedUnit = u;
                    }
                }
            }
        }

        if(!armies[turn % armies.size()]->isAnimating())
            armies[turn % armies.size()]->action(pointedUnit, mousePtr, event.mouseButton.button);
    }

    if(event.type == sf::Event::KeyPressed) 
    {
        if(event.key.code == sf::Keyboard::Space) 
        {
            if(!armies[turn % armies.size()]->isAnimating())
            {
                armies[turn % armies.size()]->endMove();
                turn++;
                armies[turn % armies.size()]->newMove();

                cout << "turn " << turn << endl;
            }
        }
    }
}

void World::update(float delta, sf::Vector2f _cameraPosition)
{
    cameraPosition = _cameraPosition;
    
    for(Army* a : armies)
        a->update(delta);
}

void World::render(sf::RenderWindow& window)
{
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //     mainPlayer->accelerate(PLAYER_ACCELERATION*UP);

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //     mainPlayer->accelerate(PLAYER_ACCELERATION*LEFT);

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //     mainPlayer->accelerate(PLAYER_ACCELERATION*DOWN);

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //     mainPlayer->accelerate(PLAYER_ACCELERATION*RIGHT);

    // if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //     Bullet* b;
    //     if(b = mainPlayer->shoot()) 
    //         objects.insert(b);
    // }

    

    for(auto o : objects) 
        o->render(window);

    for(auto a : armies)
        a->render(window);

}

World::~World()
{
    for(auto a : armies){
        delete a;
    }
}