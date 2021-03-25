#include "World.h"
#include "consts.h"

World::World() :
    camera(sf::FloatRect(0, 0, 1080, 720)),
    map( 8*size_screen_in_block_h, 8*size_screen_in_block_w, 100, 100, size_elemantary_block_in_pixel * pixel_size, 1)
{

    armies.push_back(new Army(0));
    armies.push_back(new Army(1));
    activeArmy = armies[0];
    activeArmy->newMove();
    map.render();
}

void World::passEvent(sf::Event event, sf::RenderWindow& window)
{ 
    if(event.type == sf::Event::MouseButtonPressed)
    {
        // Calculate click target

        sf::Vector2f mousePtr(sf::Mouse::getPosition(window));
        mousePtr += camera.getCenter() - windowDims * 0.5f;
        
        float normToUnit = 400; // max dist to detect click
        Unit* pointedUnit = 0;
        for(auto a : armies) 
        {
            for(auto u : *a->getUnits()) 
            {
                if(normToUnit > norm(u->getPosition() - mousePtr) ) 
                {
                    normToUnit = normToUnit;
                    pointedUnit = u;
                }
            }
        }

        if(!activeArmy->isAnimating())
            activeArmy->action(pointedUnit, mousePtr, event.mouseButton.button);
        
    }

    if(event.type == sf::Event::KeyPressed) 
    {
        if(event.key.code == sf::Keyboard::Space) 
        {
            if(!activeArmy->isAnimating())
            {
                activeArmy->endMove();
                activeArmy = armies[(++turn) % armies.size()];
                activeArmy->newMove();

                cout << "turn " << turn << endl;
            }
        }
    }
}

void World::update(float delta)
{
    
    for(Army* a : armies)
        a->update(delta);
}

void World::render(sf::RenderWindow& window, bool active)
{
    if(active)
    {
        if(sf::Mouse::getPosition(window).x < 100)
            camera.move(LEFT * CAMERA_SPEED);
        if(sf::Mouse::getPosition(window).x > windowWidth-100)
            camera.move(RIGHT * CAMERA_SPEED);
        if(sf::Mouse::getPosition(window).y < 100)
            camera.move(UP * CAMERA_SPEED);
        if(sf::Mouse::getPosition(window).y > windowHeight-100)
            camera.move(DOWN * CAMERA_SPEED);
    }

    window.setView(camera);

    map.draw(window, {0, 0});

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