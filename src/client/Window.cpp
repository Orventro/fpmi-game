#include "Window.h"

GameWindow::GameWindow(sf::Vector2f size) : window(sf::VideoMode(size.x, size.y), "fpmi-game")
{
    // init rng
#ifdef MULTIPLAYER
    rng = std::mt19937(client.seed);
    myArmyId = client.id;
#endif

    world = new World(size);
    window.setFramerateLimit(FPS);
#ifdef MULTIPLAYER
    if (world->getAAId() == myArmyId)
        setState(STATE_NEUTRAL);
    else
        setState(STATE_WAITING);
#else
    setState(STATE_NEUTRAL);
#endif
    if (!defaultFont.loadFromMemory(__res_fonts_Oswald_ttf, __res_fonts_Oswald_ttf_len))
    {
        cout << "Error! Cannot load font from memory!\n";
        exit(1);
    }

    hint.setFont(defaultFont);
    hint.setFillColor(sf::Color(29, 30, 31, 255));
    hint.setPosition(sf::Vector2f(-window.getSize().x, window.getSize().y) * 0.5f + HINT_OFFSET);
    hint.setCharacterSize(20);

    for (int i = 0; i < 4; i++)
        hints[STATE_CHOOSING] += std::to_string(i + 1) + " (" + std::to_string(Price_unit[i]) + " gold), ";

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
        else if (event.type == sf::Event::Resized)
        {
            world->onResized(sf::Vector2f(window.getSize()));
            goldAmount.setPosition(sf::Vector2f(window.getSize().x, -(float)window.getSize().y) * 0.5f + GOLD_OFFSET);
            hint.setPosition(sf::Vector2f(-(float)window.getSize().x, window.getSize().y) * 0.5f + HINT_OFFSET);
        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            return 1;
        }
        else if ((state != &GameWindow::waiting) & (state != &GameWindow::finish))
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                world->newMove();
#ifdef MULTIPLAYER
                setState(STATE_WAITING);
                send(END_MOVE);
#else
                setState(STATE_NEUTRAL);
                goldAmount.setString("GOLD: " + std::to_string(world->getAAGold()));
#endif
            }
            else if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Right))
            {
                if (world->unselect())
                    setState(STATE_NEUTRAL);
            }
            else
                std::invoke(state, this, event); // C++17
        }
        else
            std::invoke(state, this, event); // C++17
    }

    window.clear();

    world->render(window, 1.0f / FPS, (state == &GameWindow::unit_selected) | (state == &GameWindow::place_new_unit), state == &GameWindow::unit_selected);

    sf::View v = window.getView();
    v.setCenter({0, 0});
    window.setView(v);
    window.draw(goldAmount);
    window.draw(hint);

    window.display();

    return 0;
}

void GameWindow::waiting(sf::Event event)
{
#ifdef MULTIPLAYER
    // cout << "mp\n";
    while (!client.recv_buf.empty())
    {
        std::string s = std::move(client.recv_buf.front());
        client.recv_buf.pop();
        int num, t;
        float x, y;
        sscanf(s.c_str(), "%d", &t);
        ACTION type = ACTION(t);
        switch (type)
        {
        case END_MOVE:
            world->newMove();
            cout << "new move\n";
            if (world->getAAId() == myArmyId)
            {
                setState(STATE_NEUTRAL);
                goldAmount.setString("GOLD: " + std::to_string(world->getAAGold()));
            }
            break;
        case NEW_UNIT:
            cout << "new unit\n";
            sscanf(s.c_str(), "%d %d %f %f", &t, &num, &x, &y);
            world->recruit(sf::Vector2f(x, y), num);
            break;
        case UNIT_ACTION:
            sscanf(s.c_str(), "%d %d %f %f", &t, &num, &x, &y);
            // cout << "unit action " << sf::Vector2f(x, y) << ' ' << num << endl;
            world->selectUnit(num);
            world->action(sf::Vector2f(x, y));
            break;
        case END_GAME:
            setState(STATE_FINISH);
            break;
        default:
            cout << "could not interpret " << type << endl;
        }
    }
#endif
}

void GameWindow::neutral(sf::Event event)
{
    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(sf::Mouse::getPosition(window));
        world->transformPoint(mousePtr);
        if (world->selectUnit(mousePtr))
            setState(STATE_SELECTED);
    }

    if ((event.type == sf::Event::KeyPressed) & (event.key.code == sf::Keyboard::N))
        if (world->unselect())
            setState(STATE_CHOOSING);
}

#ifdef MULTIPLAYER
void GameWindow::send(ACTION actionType, int num, sf::Vector2f vec)
{
    std::string message;
    char *c = reinterpret_cast<char *>(&actionType);
    message += std::to_string((int)actionType) + " ";
    if (actionType == NEW_UNIT | actionType == UNIT_ACTION)
    {
        std::tuple<sf::Vector2f, int> info(vec, num);
        c = reinterpret_cast<char *>(&info);
        // message += std::string(c, sizeof(std::tuple<sf::Vector2f, int>));
        message += std::to_string(num) + " " + std::to_string(vec.x) + " " + std::to_string(vec.y);
        cout << "send " << ' ' << num << ' ' << vec << '\n';
    }
    else
        cout << "nm " << endl;
    client.send_Client(message);
}
#endif

void GameWindow::unit_selected(sf::Event event)
{

    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(sf::Mouse::getPosition(window));
        world->transformPoint(mousePtr);
        if (world->action(mousePtr))
        {
#ifdef MULTIPLAYER
            send(UNIT_ACTION, world->getSelected()->getId(), mousePtr);
#endif
        }
    }
}

void GameWindow::choose_new_unit(sf::Event event)
{
    type_of_new_unit = -1;

    switch (event.key.code)
    {
    case sf::Keyboard::Num1:
        type_of_new_unit = 1;
        break;
    case sf::Keyboard::Num2:
        type_of_new_unit = 2;
        break;
    case sf::Keyboard::Num3:
        type_of_new_unit = 3;
        break;
    case sf::Keyboard::Num4:
        type_of_new_unit = 4;
        break;
    default:
        type_of_new_unit = -1;
        break;
    }

    if ((event.type == sf::Event::KeyPressed) & (type_of_new_unit != -1))
        if (world->unselect())
            setState(STATE_PLACING);
}

void GameWindow::place_new_unit(sf::Event event)
{

    if ((event.type == sf::Event::MouseButtonPressed) & (event.mouseButton.button == sf::Mouse::Left))
    {
        sf::Vector2f mousePtr(sf::Mouse::getPosition(window));
        world->transformPoint(mousePtr);
        if (world->recruit(mousePtr, type_of_new_unit))
        {
            setState(STATE_NEUTRAL);
            goldAmount.setString("GOLD: " + std::to_string(world->getAAGold()));
#ifdef MULTIPLAYER
            send(NEW_UNIT, type_of_new_unit, mousePtr);
#endif
        }
    }
}

void GameWindow::finish(sf::Event event)
{
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