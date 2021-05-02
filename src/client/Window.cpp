#include "Window.h"

GameWindow::GameWindow(sf::Vector2f size) : window(sf::VideoMode(size.x, size.y), "fpmi-game")
{
    cout << "ok1\n";
    world = new World(size);
    window.setFramerateLimit(FPS);
    state = &GameWindow::neutral;

    if (!defaultFont.loadFromMemory(__res_fonts_Oswald_ttf, __res_fonts_Oswald_ttf_len))
    {
        cout << "Error! Cannot load font from memory!\n";
        exit(1);
    }

    goldAmount.setString("GOLD: " + std::to_string(START_GOLD));
    goldAmount.setFillColor(GOLD_COLOR);
    goldAmount.setCharacterSize(20);

    if (!goldFont.loadFromMemory(__res_fonts_Freshman_ttf, __res_fonts_Freshman_ttf_len))
    {
        cout << "Error! Cannot load font from memory!\n";
        exit(1);
    }
    goldAmount.setFont(goldFont);
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
        else if (event.type == sf::Event::Resized) {
            world->onResized(sf::Vector2f(window.getSize()));
            goldAmount.setPosition(sf::Vector2f(window.getSize())*0.5f + GOLD_OFFSET);
        }
        else if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::Space))
        {
            world->newMove();
            goldAmount.setString("GOLD: " + std::to_string(world->getGold()));
            state = &GameWindow::neutral;
        }
        else if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Right))
        {
            if (world->unselect())
                state = &GameWindow::neutral;
        }
        else
            std::invoke(state, this, event); // C++17
    }

    window.clear();

    world->render(window, 1.0f / FPS, (state == &GameWindow::unit_selected) | (state == &GameWindow::place_new_unit), state == &GameWindow::unit_selected);

    sf::View v = window.getView();
    v.setCenter({0,0});
    window.setView(v);
    window.draw(goldAmount);

    window.display();

    return 0;
}

void GameWindow::neutral(sf::Event event)
{
    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(event.mouseMove.y, event.mouseWheelScroll.x); // but why??? idk seems to be a bug of sfml
        if (world->selectUnit(mousePtr))
        {
            state = &GameWindow::unit_selected;
        }
    }

    if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::N))
        if (world->unselect())
            state = &GameWindow::choose_new_unit;
}

void GameWindow::unit_selected(sf::Event event)
{

    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(event.mouseMove.y, event.mouseWheelScroll.x);
        world->action(mousePtr);
    }
}

void GameWindow::choose_new_unit(sf::Event event)
{
    if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::Num1))
        if (world->unselect())
            state = &GameWindow::place_new_unit;
}

void GameWindow::place_new_unit(sf::Event event)
{

    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(event.mouseMove.y, event.mouseWheelScroll.x);
        if (world->recruit(mousePtr, 1)) { // сейчас толко 1 тип 
            state = &GameWindow::neutral;
            goldAmount.setString("GOLD: " + std::to_string(world->getGold()));
        }
    }
}

GameWindow::~GameWindow()
{
    delete world;
}