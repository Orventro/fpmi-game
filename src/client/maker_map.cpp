#include "maker_map.h"
#include "consts.h"

maker_map:: maker_map( 	size_t size_h ,size_t size_w, size_t step_h , size_t step_w , size_t _sprite_size, time_t seed) 
{
	height = size_h ;
	width = size_w ;
	step_node_h  = step_h ;
	step_node_w  = step_w;

    std::vector<std::vector<double> > block_seeds_color ( height, std::vector<double> (width , -1.0) );
    type_block.resize(height, std::vector<unsigned int> (width) );
    

    perlin_noise P ( seed,  step_node_h,  step_node_w );
    P.generation(block_seeds_color);

    painter PA (90, 115, block_seeds_color );
    PA.set_type_block (block_seeds_color, type_block);

    uint8_t* pixels = new uint8_t[width*height*4];
    this->image_map.create(width, height, pixels);
}

maker_map:: ~maker_map () 
{
}

void maker_map::render()
{
    for(uint x = 0; x < width; ++x)
        for (uint y = 0; y < height; ++y ) {
            image_map.setPixel(x, y, TERRAIN_COLORS[type_block[y][x]]);
        }

    mapTexture.loadFromImage(image_map);
    mapSprite.setTexture(mapTexture);
}

void maker_map:: draw (sf::RenderWindow &window, const sf::Vector2f center  ) 
{
    window.draw(mapSprite);  
}