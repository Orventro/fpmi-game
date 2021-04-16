#include "town.h"

town::town () 
{   
    numb_player = 0;
    none.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/none.png");
    none.createMaskFromColor(sf::Color(255,255, 255));
    red.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/red.png");
    red.createMaskFromColor(sf::Color(255,255, 255));
    blue.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/blue.png");
}


town:: town( const sf::Vector2f &pos , const unsigned int pl ) 
{
    coord = pos;
    numb_player = pl;
    none.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/none.png");
    none.createMaskFromColor(sf::Color(255,255, 255));
    red.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/red.png");
    red.createMaskFromColor(sf::Color(255,255, 255));
    blue.loadFromFile("/home/ilya/vs_code_projects/fpmi-game/res/points/blue.png");
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