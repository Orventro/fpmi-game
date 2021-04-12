#include "World.h"
#include "consts.h"

World::World(GameWindow* _window, sf::Vector2f _size) :
    gameWindow(_window),
    size(_size),
    camera(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y)),
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

void World::passEvent(sf::Event event, sf::RenderWindow& renderWindow)
{ 
    if(event.type == sf::Event::MouseButtonPressed)
    {
        // Calculate click target

        sf::Vector2f mousePtr(sf::Mouse::getPosition(renderWindow));
        mousePtr += camera.getCenter() - sf::Vector2f(gameWindow->getSize()) * 0.5f;
        
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
        else if(event.key.code == sf::Keyboard::N)
        {
            if(!activeArmy->isAnimating())
            {
                activeArmy->recruit();
                gold_amount.setString("GOLD: " + std::to_string(activeArmy->getGold()));
            }
        }
    }
}

float move_speed(float x, float range)
{
    if(x >= 0)
        return std::max(1.0f/(x/range*5+2.5f) - 0.3f, 0.0f) * 20 * range;
    else 
        return 0;
}

void World::render(sf::RenderWindow& renderWindow, float delta, bool active)
{
    for(Army* a : armies)
        a->update(delta);
    
    if(active)
    {
        int x = sf::Mouse::getPosition(renderWindow).x;
        int y = sf::Mouse::getPosition(renderWindow).y;
        float adjDelta = std::min(delta, 1.0f);

        float winWidth = gameWindow->getSize().x,
             winHeight = gameWindow->getSize().y;

        // moving camera
        camera.move(move_speed(x, winWidth) * LEFT * adjDelta);
        camera.move(move_speed(winWidth - x, winWidth) * RIGHT * adjDelta);
        camera.move(move_speed(y, winHeight) * UP * adjDelta);
        camera.move(move_speed(winHeight - y, winHeight) * DOWN * adjDelta);
        
        // no escaping out of the world
        if(camera.getCenter().x - winWidth/2 <= 0) 
            camera.setCenter({winWidth/2, camera.getCenter().y});
        if(camera.getCenter().x - size.x + winWidth/2 >= 0)
            camera.setCenter({size.x - winWidth/2, camera.getCenter().y});
        if(camera.getCenter().y - winHeight/2 <= 0)
            camera.setCenter({camera.getCenter().x, winHeight/2});
        if(camera.getCenter().y - size.y + winHeight/2 >= 0)
            camera.setCenter({camera.getCenter().x, size.y - winHeight/2});

    }

    renderWindow.setView(camera);

    map.draw(renderWindow, {0, 0});

    for(auto o : objects) 
        o->render(renderWindow);

    for(auto a : armies)
        a->render(renderWindow);

    gold_amount.setOrigin(-camera.getCenter() + sf::Vector2f(gameWindow->getSize()) * 0.5f + GOLD_OFFSET); // why neg?
    renderWindow.draw(gold_amount);

}

const vector<Army*>& World::getArmies() const
{
    return armies;
}

void World::onResized()
{
    sf::Vector2f center = camera.getCenter();
    camera = sf::View(sf::FloatRect(0, 0, gameWindow->getSize().x, gameWindow->getSize().y));
    camera.setCenter(center);
}

World::~World()
{
    for(auto a : armies){
        delete a;
    }
}