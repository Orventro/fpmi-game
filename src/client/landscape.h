#pragma once

#include <SFML/Graphics.hpp>


class landscape
{
public:
	
	landscape( 	size_t _x ,size_t _y, size_t _range) ;
	
	~landscape() ;

	virtual void draw (sf::RenderWindow &window, size_t sprite_size ); 
	virtual void set_parameters ( size_t _x ,size_t _y, size_t _range ) ;
protected:
	size_t x;
	size_t y;
	size_t range;
	sf::Texture texture;
	
};

class water_block : public landscape 
{

public:	
	water_block( size_t _x ,size_t _y, size_t _range ) : landscape (_x, _y, _range)
	{
		texture.loadFromFile("texture/water.jpg");
	}
	~water_block() 
	{

	}
};

class sand_block : public landscape 
{
public:
	sand_block( size_t _x ,size_t _y, size_t _range ) : landscape (_x, _y, _range)
	{
		texture.loadFromFile("texture/sand.jpg");
	}
	~sand_block() 
	{

	}
};

class grass_block : public landscape 
{
public:
	grass_block( size_t _x ,size_t _y, size_t _range ) : landscape ( _x, _y, _range)
	{
		texture.loadFromFile("texture/grass.jpg");
	}
	~grass_block() 
	{

	}
};