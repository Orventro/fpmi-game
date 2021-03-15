#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <iostream>

using std::set;
using std::cout;
using std::endl;
using std::vector;
using timestamp = std::chrono::_V2::system_clock::time_point;

const sf::Vector2f UP   ( 0, -1);
const sf::Vector2f DOWN ( 0,  1);
const sf::Vector2f LEFT (-1,  0);
const sf::Vector2f RIGHT( 1,  0);

const int windowWidth = 1080;
const int windowHeight = 720;

const sf::Vector2f windowDims(windowWidth, windowHeight);

const std::chrono::milliseconds RELOAD_TIME(200);

float norm(sf::Vector2f v);
std::ostream& operator<<(std::ostream& os, const sf::Vector2f& v);

const sf::Color ARMY_COLORS[] = {sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green};

const sf::Vector2f ARMY_POSITIONS[] = {sf::Vector2f(20, 20), sf::Vector2f(20, 400), sf::Vector2f(400, 20), sf::Vector2f(400, 400)};

const sf::Color SELECT_COLOR(20, 250, 20, 90);
const sf::Color MOVE_COLOR(160, 220, 10, 50);
const sf::Color ATTACK_COLOR(240, 50, 10, 70);
