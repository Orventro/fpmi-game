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


class maker_map
{
public:
	
	maker_map( 	size_t size_h ,size_t size_w, size_t step_h , size_t step_w , size_t sprite_size, time_t seed);
	~maker_map();

	struct type_distance {
    	unsigned int x;
    	unsigned int y;
    	unsigned int distance;
    	
    	type_distance ( unsigned int x, unsigned int y  , unsigned int distance) {
        	this->x = x;
        	this->y = y;
        	this->distance = distance;
    	}

    	bool operator < ( const type_distance &A ) 
    	{
    		return this->distance < A.distance;
    	}
	};

	void render();

	void  draw (sf::RenderWindow &window, const sf::Vector2f center  );

private:
	size_t height;
	size_t width;
	size_t step_node_h ;
	size_t step_node_w ;
	sf::Image image_map;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	std::vector<std::vector< unsigned int> > type_block;
	std::vector<std::vector< unsigned int> > distance_neighborhood_biom;


	std::pair<unsigned int, unsigned int>  get_window_size_in_blocks ( sf::RenderWindow &window ) ;
	void draw_block_water ( std::pair<size_t, size_t> otn_coord  );
	void draw_block_sand ( std::pair<size_t, size_t> otn_coord  );
	void draw_block_grass ( std::pair<size_t, size_t> otn_coord  );

	void draw_block(sf::Vector2u otn_coord, int type);

};