#include "painter.h"

void painter::set_type_block (  std::vector<std::vector<double> > &block_seeds_color , std::vector<std::vector<unsigned int> > &type_block ) {
	for ( size_t x = 0; x < size_screen_in_block_h ; ++x )
		for ( size_t y = 0; y < size_screen_in_block_w ; ++y ) {
			double col = block_seeds_color[x][y]*250;
    		if ( col <= board_water ) 
        		type_block[x][y] = 1;
    		else {
        		if ( col <= board_sand ) 
            		type_block[x][y]= 2;
        		else 
            		type_block[x][y] = 3;
    		}
		}
}


bool painter:: check_neighborhood ( unsigned int x, unsigned int y, std::vector<std::vector<unsigned int> > &type_block ) {
    if ( type_block[x][y] != type_block[x-1][y] )
        return false;
    if ( type_block[x][y] != type_block[x+1][y] )
        return false;
    if ( type_block[x][y] != type_block[x][y-1] )
        return false;
    if ( type_block[x][y] != type_block[x][y+1] )
        return false;
    if ( type_block[x][y] != type_block[x-1][y-1] )
        return false;
    if ( type_block[x][y] != type_block[x-1][y+1] )
        return false;
    if ( type_block[x][y] != type_block[x+1][y-1] )
        return false;
    if ( type_block[x][y] != type_block[x+1][y+1] )
        return false;
    return true;
}

void painter:: get_board_bioms ( std::vector<std::vector<unsigned int> > &type_block, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom) {
    for ( unsigned int x = 1; x <  size_screen_in_block_h -1; ++x )
        for ( unsigned int y = 1; y <  size_screen_in_block_w - 1 ; ++y ) {
            if ( ! painter:: check_neighborhood (x, y, type_block) )
                distance_neighborhood_biom[x][y] = 1;
        }
    for ( unsigned int y = 0; y < size_screen_in_block_w; ++y )
        distance_neighborhood_biom[0][y] = distance_neighborhood_biom[size_screen_in_block_h-1][y] = 1;
    for ( unsigned int x = 0; x < size_screen_in_block_h; ++x )
        distance_neighborhood_biom[x][0] = distance_neighborhood_biom[x][size_screen_in_block_w-1] = 1;
}

bool painter:: check_neighborhood_distance ( unsigned int x, unsigned int y, unsigned int d, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom ) {
    if ( d == distance_neighborhood_biom[x-1][y] )
        return false;
    if (   d == distance_neighborhood_biom[x+1][y] )
        return false;
    if (  d == distance_neighborhood_biom[x][y-1] )
        return false;
    if ( d == distance_neighborhood_biom[x][y+1] )
        return false;
    if ( d == distance_neighborhood_biom[x-1][y-1] )
        return false;
    if ( d  == distance_neighborhood_biom[x-1][y+1] )
        return false;
    if ( d == distance_neighborhood_biom[x+1][y-1] )
        return false;
    if ( d == distance_neighborhood_biom[x+1][y+1] )
        return false;
    return true;
}



void painter:: get_distance_neighborhood_biom ( std::vector<std::vector<unsigned int> > &type_block, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom) {
    painter:: get_board_bioms(type_block, distance_neighborhood_biom);
    unsigned int delta = 1;
    bool flag_change = true ;
    while ( flag_change ) {
        flag_change = false;
        for ( unsigned int x = 1;  x <  size_screen_in_block_h - 1; ++x ){
            for ( unsigned int y= 1; y < size_screen_in_block_w-1; ++y ) {
                if ( distance_neighborhood_biom[x][y] == 0 ) {
                    flag_change = true;
                    if ( ! painter:: check_neighborhood_distance(x, y, delta, distance_neighborhood_biom) ) {
                        distance_neighborhood_biom[x][y] = delta+1;
                    }
                }
            }
       }
       ++delta;
        }
}

