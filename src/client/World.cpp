#include "World.h"
#include "consts.h"

World::World(sf::Vector2f _size) :
    size(_size),
    camera(sf::FloatRect(0, 0, windowWidth, windowHeight)),
    map(_size.y, _size.x, 100, 100, size_elemantary_block_in_pixel * pixel_size, 1)
{
    armies.push_back(new Army(0));
    armies.push_back(new Army(1));
    activeArmy = armies[0];
    activeArmy->newMove();
    gold_amount.setString("GOLD: " + std::to_string(activeArmy->getGold()));
    map.render();
    camera.setCenter(size.x/2, size.y/2);

    gold_amount.setFillColor(GOLD_COLOR);
    gold_amount.setCharacterSize(20);

    if (!gold_font.loadFromMemory(__res_fonts_Freshman_ttf, __res_fonts_Freshman_ttf_len))
    {
        cout << "Error! Cannot load font from memory!\n";
        exit(1);
    }
    gold_amount.setFont(gold_font);
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
                gold_amount.setString("GOLD: " + std::to_string(activeArmy->getGold()));

                cout << "turn " << turn << endl;
            }
        }
    }
}

float move_speed(float x)
{
    if(x >= 0)
        return std::max(1.0f/(x/windowWidth*5+2.5f) - 0.3f, 0.0f) * 20 * windowWidth;
    else 
        return 0;
}

void World::render(sf::RenderWindow& window, float delta, bool active)
{
    for(Army* a : armies)
        a->update(delta);
    
    if(active)
    {
        int x = sf::Mouse::getPosition(window).x;
        int y = sf::Mouse::getPosition(window).y;
        float adjDelta = std::min(delta, 1.0f);

        // moving camera
        camera.move(move_speed(x) * LEFT * adjDelta);
        camera.move(move_speed(windowWidth - x) * RIGHT * adjDelta);
        camera.move(move_speed(y) * UP * adjDelta);
        camera.move(move_speed(windowHeight - y) * DOWN * adjDelta);
        
        // no escaping out of the world
        if(camera.getCenter().x - windowWidth/2 <= 0) 
            camera.setCenter({windowWidth/2, camera.getCenter().y});
        if(camera.getCenter().x - size.x + windowWidth/2 >= 0)
            camera.setCenter({size.x - windowWidth/2, camera.getCenter().y});
        if(camera.getCenter().y - windowHeight/2 <= 0)
            camera.setCenter({camera.getCenter().x, windowHeight/2});
        if(camera.getCenter().y - size.y + windowHeight/2 >= 0)
            camera.setCenter({camera.getCenter().x, size.y - windowHeight/2});

    }

    window.setView(camera);

    map.draw(window, {0, 0});

    for(auto o : objects) 
        o->render(window);

    for(auto a : armies)
        a->render(window);

    gold_amount.setOrigin(-camera.getCenter() + windowDims * 0.5f + GOLD_OFFSET); // why neg?
    window.draw(gold_amount);

}

const vector<Army*>& World::getArmies() const
{
    return armies;
}

World::~World()
{
    for(auto a : armies){
        delete a;
    }
}