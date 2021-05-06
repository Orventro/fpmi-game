#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <deque>

#include "consts.h"
#include "Town.h"
#include "perlin_noise.h"
#include "painter.h"

class WorldMap
{
public:
	sf::Image image_map;

	WorldMap(int size_h, int size_w, int step_h, int step_w, time_t seed);
	~WorldMap();	

	std::pair<sf::Vector2f, sf::Vector2f> start_coord;

	void render();
	void renderBorder(sf::Vector2u start, float dist);
	void draw(sf::RenderWindow &window, bool draw_town_radius, bool draw_movement_border);
	void create_towns();
	void change_player(Town *t, int pl);
	const std::vector<Town*>& getTowns() const;
	std::pair<std::deque<sf::Vector2f>, float> getPath(sf::Vector2f point);
	void get_start_towns();

private:

	const int propSize = 5;

	const int height;
	const int width;
	const int step_node_h;
	const int step_node_w;
	uint8_t *mapPixels, *borderPixels;
	sf::Image borderImage;
	sf::Texture mapTexture, borderTexture;
	sf::Sprite mapSprite, borderSprite;
	std::vector<Town *> towns;
	sf::CircleShape townRadius;

	std::vector<std::vector<unsigned int>> type_block;
	std::vector<std::vector<unsigned int>> distance_neighborhood_biom;
	std::vector<float> distanceMatr;
	std::vector<std::vector<float>> hypot_cache;

	std::pair<unsigned int, unsigned int> get_window_size_in_blocks(sf::RenderWindow &window);

	bool check_distance_water(const sf::Vector2u coord);
	bool check_distance_town(const sf::Vector2f coord);
	void create_one_town();
	void prop(int x, int y);
	bool moveBackwards(int &x, int &y);
	bool isBorder(int x, int y);


	Town *closestTown(const sf::Vector2u coord);
};