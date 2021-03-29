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
        if (event.type == sf::Event::Closed)
            window.close();
        else 
            world->passEvent(event, window);
    }
    // int x = sf::Mouse::getPosition(window).x;
    // int y = sf::Mouse::getPosition(window).y;
    // if(x >= 0 && y >= 0 && x <= windowWidth && y <= windowHeight)
    //     inFocus = 1;
    // else
    //     inFocus = 0;

    window.clear();

    world->render(window, 1.0f/FPS, 1);

    window.display();

    return 0;
}

GameWindow::~GameWindow()
{
    delete world;
}