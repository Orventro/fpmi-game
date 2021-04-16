#include "town.h"

town::town () 
{   
    numb_player = 0;
    none.loadFromMemory( __res_points_none_png, __res_points_none_png_len);
    none.createMaskFromColor(sf::Color(255,255, 255));
    red.loadFromMemory(__res_points_red_png, __res_points_red_png_len  );
    red.createMaskFromColor(sf::Color(255,255, 255));
    blue.loadFromMemory( __res_points_blue_png, __res_points_blue_png_len);
}


town:: town( const sf::Vector2f &pos , const unsigned int pl ) 
{
    coord = pos;
    numb_player = pl;
    none.loadFromMemory( __res_points_none_png, __res_points_none_png_len);
    none.createMaskFromColor(sf::Color(255,255, 255));
    red.loadFromMemory(__res_points_red_png, __res_points_red_png_len  );
    red.createMaskFromColor(sf::Color(255,255, 255));
    blue.loadFromMemory( __res_points_blue_png, __res_points_blue_png_len); 
    blue.createMaskFromColor(sf::Color(255,255, 255));
}
town:: ~town () 
{

}

sf::Vector2f town::get_coord () 
{
    return this->coord;
}

 unsigned int town::get_player () 
 {
     return this->numb_player;
 }

 void town::change_player ( const unsigned int pl, sf::Image* map) 
 {
     this->numb_player = pl;
     switch ( pl  )
     {
     case 0 :
            map->copy( none, coord.x, coord.y, sf::IntRect(0, 0, 0, 0), true);
            break;    
     case 1 :
            map->copy( blue, coord.x, coord.y, sf::IntRect(0, 0, 0, 0), true); 
            break;
     case 2 :
            map->copy( red, coord.x, coord.y, sf::IntRect(0, 0, 0, 0), true);
            break;
     default:
            break;
     }
 }