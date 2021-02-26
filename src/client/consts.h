#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using timestamp = chrono::_V2::system_clock::time_point;

const sf::Vector2f UP   ( 0, -1);
const sf::Vector2f DOWN ( 0,  1);
const sf::Vector2f LEFT (-1,  0);
const sf::Vector2f RIGHT( 1,  0);

const float PLAYER_ACCELERATION = 1.5;
const float BULLET_SPEED = 30;

const int windowWidth = 1080;
const int windowHeight = 720;

const sf::Vector2f windowDims(windowWidth, windowHeight);

const chrono::milliseconds RELOAD_TIME(200);