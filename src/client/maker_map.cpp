#include "maker_map.h"
#include "consts.h"

maker_map:: maker_map(size_t size_h ,size_t size_w, size_t step_h , size_t step_w , size_t _sprite_size, time_t seed) 
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
    for ( auto it : Towns )
        delete it;
}

void maker_map::render()
{
    for(uint x = 0; x < width; ++x)
        for (uint y = 0; y < height; ++y ) {
            image_map.setPixel(x, y, TERRAIN_COLORS[type_block[y][x]]);
        }
    this->create_towns();   
    mapTexture.loadFromImage(image_map);
    mapSprite.setTexture(mapTexture);
}

void maker_map:: draw (sf::RenderWindow &window, const sf::Vector2f center  ) 
{
    window.draw(mapSprite);  
}

bool maker_map:: check_distance_town (  const sf::Vector2u &coord ) 
{
    for ( auto it : this->Towns )   
        if ( ( it->coord.x- coord.x)*(it->coord.x- coord.x) + ( it->coord.y- coord.y)*(it->coord.y- coord.y) < 10000 )
            return false;
    return true;        
}

bool maker_map:: check_distance_water ( const sf::Vector2u &coord ) 
{
    int delta = 50 ;  
    for ( size_t i = std::max(0 , (int) ( (int)coord.x -delta )); i < std::min( (int)width , (int) (coord.x +delta )); ++i ) 
    {
        for ( size_t j = std::max(0 , (int) ( (int)coord.y -delta )); j < std::min( (int)height , (int) (coord.y +delta )); ++j )
            if ( 1 == type_block[i][j] )
                return false;
    }
    return true;            
}

void maker_map::create_one_town () 
{
    bool flag_stop = false;
    unsigned int kol_wrong = 0;
    while ( !flag_stop ) 
    {   
        int delta = 60;
        size_t x = rand() % width;
        size_t y = rand() % height;
        
        if ( x < delta)
            x = delta;
        if ( x > 2000 - delta )
            x = 2000 - delta; 
        
        if ( y < delta)
            y = delta;
        if ( y > 2000 - delta )
            y = 2000 - delta;       
        
        if ( maker_map::check_distance_town(sf::Vector2u(x, y) ) && maker_map::check_distance_water(sf::Vector2u(y, x) ) ) 
        {
            flag_stop = true;
            Towns.push_back ( new town( sf::Vector2f(x, y), 1));
        }
        else
            ++kol_wrong;
        if ( kol_wrong >= 1000 )
            return;
    }
}

void maker_map::create_towns() 
{
    for ( size_t i = 0; i < 40; ++i )
        maker_map::create_one_town();
    for ( auto it : Towns ) 
        it->change_player(0, &image_map);    
}

void maker_map::change_player ( town* t, int pl ) 
{
    t->change_player(pl, &image_map);   
    mapTexture.loadFromImage(image_map);
    mapSprite.setTexture(mapTexture);
    
}

