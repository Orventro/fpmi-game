#include "Window.h"

GameWindow::GameWindow(sf::Vector2f size) : window(sf::VideoMode(size.x, size.y), "fpmi-game")
{
    world = new World(size);
    window.setFramerateLimit(FPS);
    setState(STATE_NEUTRAL);

    if (!defaultFont.loadFromMemory(__res_fonts_Oswald_ttf, __res_fonts_Oswald_ttf_len))
    {
        cout << "Error! Cannot load font from memory!\n";
        exit(1);
    }

    hint.setFont(defaultFont);
    hint.setFillColor(sf::Color(29, 30, 31, 255));
    hint.setPosition(sf::Vector2f(-window.getSize().x, window.getSize().y)*0.5f + HINT_OFFSET);
    hint.setCharacterSize(20);

    for(int i = 0; i < 4; i++)
        hints[STATE_CHOOSING] += std::to_string(i+1) + " (" + std::to_string(UNIT_COST[i]) + " gold), ";

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
            goldAmount.setPosition(sf::Vector2f(window.getSize().x, -(float)window.getSize().y)*0.5f + GOLD_OFFSET);
            hint.setPosition(sf::Vector2f(-(float)window.getSize().x, window.getSize().y)*0.5f + HINT_OFFSET);
        }
        else if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::Space))
        {
            world->newMove();
            goldAmount.setString("GOLD: " + std::to_string(world->getGold()));
            setState(STATE_NEUTRAL);
        }
        else if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::Escape))
        {
            return 1;
        }
        else if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Right))
        {
            if (world->unselect())
                setState(STATE_NEUTRAL);
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
    window.draw(hint);

    window.display();

    return 0;
}

void GameWindow::waiting(sf::Event event)
{

}

void GameWindow::neutral(sf::Event event)
{
    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(event.mouseMove.y, event.mouseWheelScroll.x); // but why??? idk seems to be a bug of sfml
        if (world->selectUnit(mousePtr))
            setState(STATE_SELECTED);
    }

    if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::N))
        if (world->unselect())
            setState(STATE_CHOOSING);
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
    current_type_unit = -1;

    switch ( event.key.code )
    {
    case sf::Keyboard::Num1:
        current_type_unit = 1;
        break;
    case sf::Keyboard::Num2:
        current_type_unit = 2;
        break;  
    case sf::Keyboard::Num3:
        current_type_unit = 3;
        break;
    case sf::Keyboard::Num4:
        current_type_unit = 4;
        break;
    default:
        current_type_unit = -1;
        break;
    }    

    if ((event.type == sf::Event::KeyPressed) & ( current_type_unit != -1 ))
        if (world->unselect())
            setState(STATE_PLACING);
}

void GameWindow::place_new_unit(sf::Event event)
{

    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(event.mouseMove.y, event.mouseWheelScroll.x);
        if (world->recruit(mousePtr, current_type_unit)) { // сейчас толко 1 тип 
            setState(STATE_NEUTRAL);
            goldAmount.setString("GOLD: " + std::to_string(world->getGold()));
        }
    }
}

void GameWindow::setState(int state_id)
{
    state = states[state_id];
    hint.setString(hints[state_id]);
}

GameWindow::~GameWindow()
{
    delete world;
}