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

const float CAMERA_SPEED = 5;

const int windowWidth = 1080;
const int windowHeight = 720;

const sf::Vector2f windowDims(windowWidth, windowHeight);

const std::chrono::milliseconds RELOAD_TIME(200);

float norm(sf::Vector2f v);
std::ostream& operator<<(std::ostream& os, const sf::Vector2f& v);

const sf::Color ARMY_COLORS[] = {sf::Color::Blue, sf::Color::Red, sf::Color::Yellow, sf::Color::Green};

const sf::Vector2f ARMY_POSITIONS[] = {sf::Vector2f(20, 20), sf::Vector2f(20, 400), sf::Vector2f(400, 20), sf::Vector2f(400, 400)};

const sf::Color SELECT_COLOR(20, 250, 20, 90);
const sf::Color MOVE_COLOR(160, 220, 10, 50);
const sf::Color ATTACK_COLOR(240, 50, 10, 70);

const int FPS = 60;

const sf::Vector2f HP_BAR_SIZE(60, 4);
const sf::Color HP_BACK_COL(67, 191, 36);
const sf::Color HP_FRONT_COL(153, 26, 6);
const sf::Vector2f HP_BAR_OFFSET(0, 30);

const size_t size_elemantary_block_in_pixel = 2;
const size_t pixel_size = 1.f;
const size_t size_screen_in_block_w =  std::ceil( ( (double) windowWidth) / ( size_elemantary_block_in_pixel ) );
const size_t size_screen_in_block_h =  std::ceil( ( (double) windowHeight) / ( size_elemantary_block_in_pixel ) );
const unsigned int step_node_h = 100;
const unsigned int step_node_w = 100;
const size_t rand_denominator =  10000;
const size_t sprite_size = size_elemantary_block_in_pixel * pixel_size;

const sf::Color TERRAIN_COLORS[] = {sf::Color::Black, sf::Color(0, 128, 255), sf::Color::Yellow, sf::Color::Green};