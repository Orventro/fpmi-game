#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>

#include "perlin_noise.h"
#include "painter.h"
#include "town.h"


class maker_map
{
public:
	sf::Image image_map;
	std::vector<town*> Towns;
	
	maker_map( 	size_t size_h ,size_t size_w, size_t step_h , size_t step_w , size_t sprite_size, time_t seed);
	~maker_map();


	void render();

	void  draw (sf::RenderWindow &window, const sf::Vector2f center  );

	void create_towns();

	void change_player ( town* t, int pl );


private:
	size_t height;
	size_t width;
	size_t step_node_h ;
	size_t step_node_w ;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	std::vector<std::vector< unsigned int> > type_block;
	std::vector<std::vector< unsigned int> > distance_neighborhood_biom;


	std::pair<unsigned int, unsigned int>  get_window_size_in_blocks ( sf::RenderWindow &window ) ;	

	bool check_distance_water (const sf::Vector2u &coord) ;
	bool check_distance_town( const sf::Vector2u &coord);
	void create_one_town();

};