#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point_blue.h"
#include "Point_red.h"
#include "Point_none.h"

class town
{
private:

    sf::Image 
        none, 
        red,
        blue;


public:
    sf::Vector2f coord;
    unsigned int numb_player; // 0 - none
    town();
    town( const sf::Vector2f &pos , const unsigned int pl );
    ~town();
    sf::Vector2f get_coord ();
    unsigned int get_player ();
    void change_player ( const unsigned int pl, sf::Image* map);  
};
