#include "Window.h"

GameWindow::GameWindow(sf::Vector2f size) : 
    window(sf::VideoMode(size.x, size.y), "Game Name")
{
    world = new World();

    window.setFramerateLimit(FPS);
}

int GameWindow::render()
{
    if (!window.isOpen())
        return 1; // 1 means not rendered
    
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::GainedFocus)
            inFocus = 1;
        if(event.type == sf::Event::LostFocus)
            inFocus = 0;
        
        if (event.type == sf::Event::Closed)
            window.close();
        else 
            world->passEvent(event, window);
    }

    window.clear();

    world->update(1.0f/FPS);
    
    world->render(window, inFocus);

    window.display();

    return 0;
}

GameWindow::~GameWindow()
{
    delete world;
}