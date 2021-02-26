#include "Window.h"

GameWindow::GameWindow(sf::Vector2f size) : 
    window(sf::VideoMode(size.x, size.y), "Game Name"),
    camera(sf::FloatRect(0, 0, 1080, 720))
{
    world = new World();

    window.setFramerateLimit(60);
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
            world->passEvent(event);
    }

    window.clear();

    //update camera
    sf::Vector2f MCposition = world->getMCposition();
    sf::Vector2f cameraPositon = camera.getCenter();
    camera.setCenter(MCposition*0.1f + cameraPositon*0.9f);
    window.setView(camera);
    
    world->render(window, camera.getCenter());

    window.display();

    return 0;
}