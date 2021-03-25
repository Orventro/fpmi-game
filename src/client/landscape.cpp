#include "landscape.h"

landscape:: landscape( 	size_t _x ,size_t _y, size_t _range) 
{
	x =_x;
	y = _y;
	range = _range;
}

landscape:: ~landscape() 
{

}

void landscape:: draw ( sf::RenderWindow &window, size_t sprite_size  ) 
{
	sf::Sprite S( texture, sf::IntRect(150, 150, (range)*sprite_size , (range)*sprite_size ));
    S.setPosition (x*sprite_size, y*sprite_size);
    window.draw(S);
}



void landscape:: set_parameters ( size_t _x ,size_t _y, size_t _range ) 
{
	this->x = _x;
	this->y = _y;
	this->range = _range;
} 
