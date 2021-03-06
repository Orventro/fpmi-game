#pragma once

#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <iostream>
#include <string>
#include <random>

extern std::mt19937 rng;

// классы задекларированы здесь, поскольку ссылаются друг на друга
class GameWindow;
class Army;
class World;
class WorldMap;
class Town;

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::set;
using std::vector;
using timestamp = std::chrono::steady_clock::time_point;

const sf::Vector2f UP(0, -1);
const sf::Vector2f DOWN(0, 1);
const sf::Vector2f LEFT(-1, 0);
const sf::Vector2f RIGHT(1, 0);

const float CAMERA_SPEED = 5;

const sf::Vector2f DEFAULT_WINDOW_SIZE(800, 600);

// helpful functions defined in SupportFunctions.cpp

int64_t get_microseconds(std::chrono::nanoseconds);
float norm(sf::Vector2f v);
float vlen(sf::Vector2f v);
std::ostream &operator<<(std::ostream &os, const sf::Vector2f &v);

const sf::Color ARMY_COLORS[] = {sf::Color::Blue, sf::Color::Red, sf::Color::Yellow, sf::Color::Green};
const sf::Color BLANK_TOWN_COLOR = sf::Color(73, 75, 77, 255);

const sf::Vector2f ARMY_POSITIONS[] = {sf::Vector2f(20, 20), sf::Vector2f(20, 400), sf::Vector2f(400, 20), sf::Vector2f(400, 400)};

enum ACTION
{
    NEW_UNIT,
    END_MOVE,
    UNIT_ACTION,
    END_GAME
};
// цвета элементов UI

const sf::Color WIN_COLOR(68, 199, 24, 255);
const sf::Color LOSE_COLOR(199, 53, 24, 255);
const sf::Color SELECT_COLOR(20, 250, 20, 90);
const sf::Color MOVE_COLOR(160, 220, 10, 50);
const sf::Color ATTACK_COLOR(240, 50, 10, 70);
const sf::Color GOLD_COLOR(247, 235, 10, 255);
const sf::Color TOWN_RADIUS_COLOR(199, 132, 219, 100);
const sf::Color MOVEMENT_BORDER_COLOR(97, 232, 210, 200);

const int FPS = 60;

const sf::Vector2f HP_BAR_SIZE(60, 4);
const sf::Color HP_BACK_COL(67, 191, 36);
const sf::Color HP_FRONT_COL(153, 26, 6);
const sf::Vector2f HP_BAR_OFFSET(0, 30);

const sf::Vector2f WORLD_SIZE(2000, 2000);

const size_t size_elemantary_block_in_pixel = 2;
const size_t pixel_size = 1.f;
// const size_t size_screen_in_block_w =  std::ceil( ( (double) windowWidth) / ( size_elemantary_block_in_pixel ) );
// const size_t size_screen_in_block_h =  std::ceil( ( (double) windowHeight) / ( size_elemantary_block_in_pixel ) );
const unsigned int step_node_h = 100;
const unsigned int step_node_w = 100;
const size_t rand_denominator = 10000;
const size_t sprite_size = size_elemantary_block_in_pixel * pixel_size;

// void, sea, sand, grass
const sf::Color TERRAIN_COLORS[] = {sf::Color::Black, sf::Color(32, 178, 220), sf::Color(242, 224, 62), sf::Color(65, 172, 10)};
const float TERRAIN_OBSTRUCTION[] = {0, 5, 2, 1};

const int START_GOLD = 0;

const sf::Vector2f GOLD_OFFSET(-200, 10);
const sf::Vector2f HINT_OFFSET(20, -30);

// Радиус в котором город находится под влиянием его армии и не может быть захвачен.
// Также радиус, в котором может появится новый юнит из этого города.
const float TOWN_RADIUS = 1e2;
// Во второй степени
const float TOWN_RADIUS2 = 1e4;

// unit's price
const unsigned int Price_unit[4] = {20, 30, 40, 50};

//unit's parameters : health, damage, energy, radius
const unsigned int swordsman[4] = {100, 40, 150, 50};
const unsigned int bowman[4] = {70, 40, 130, 300};
const unsigned int knight[4] = {200, 60, 100, 50};
const unsigned int cavalry[4] = {120, 35, 250, 50};