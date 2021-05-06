#include "perlin_noise.h"

double perlin_noise:: rand_double () {
    return ( (double) ( (rng() ^ rng() ) % rand_denominator) + 1) / rand_denominator;
}

void  perlin_noise:: set_node_generation ( std::vector<std::vector<double> > &block_seeds_color ) 
{
    for ( unsigned int x = 0; x < size_screen_in_block_h; x += step_node_h )
        for ( unsigned int y = 0; y < size_screen_in_block_w; y += step_node_w ) {
            block_seeds_color[x][y] = rand_double();
        }
    if ( block_seeds_color[size_screen_in_block_h-1][0] == -1.0 )
        block_seeds_color[size_screen_in_block_h-1][0] = rand_double();
    if ( block_seeds_color[size_screen_in_block_h-1][size_screen_in_block_w - 1] == -1.0 )
        block_seeds_color[size_screen_in_block_h-1][size_screen_in_block_w - 1] = rand_double();
    if ( block_seeds_color[0][size_screen_in_block_w - 1] == -1.0 )
        block_seeds_color[0][size_screen_in_block_w - 1] = rand_double();
}

double perlin_noise:: linal_inteerpol ( unsigned int x1, const double y1, unsigned int x2, const double y2, unsigned int x) 
{
    double ans = ( y2-y1 )*(x-x1)/(x2-x1) + y1;
    return ans;
}

void  perlin_noise:: find_seed_color ( const unsigned int x, const unsigned int y, std::vector<std::vector< double> > &block_seeds_color ) 
{
	unsigned int x_up = (x / step_node_h) * step_node_h;
    unsigned int x_down;
    if ( x_up + step_node_h >= size_screen_in_block_h )
        x_down = size_screen_in_block_h -1;
    else
        x_down = x_up + step_node_h;
    unsigned int y_left = (y / step_node_w) * step_node_w;
    unsigned int y_right;
    if ( y_left + step_node_w >= size_screen_in_block_w )
        y_right = size_screen_in_block_w - 1;
    else
        y_right = y_left + step_node_w;
    double a1 = linal_inteerpol(y_left, block_seeds_color[x_up][y_left], y_right, block_seeds_color[x_up][y_right], y );
    double a2 = linal_inteerpol(y_left, block_seeds_color[x_down][y_left], y_right, block_seeds_color[x_down][y_right], y );
    block_seeds_color[x][y] = linal_inteerpol( x_up, a1, x_down, a2, x );
}

void perlin_noise:: get_board_const_x ( const unsigned int x , std::vector<std::vector<double> > &block_seeds_color  )
 {
    for ( size_t y = 0 ; y < size_screen_in_block_w; ++y ) {
        if ( block_seeds_color[x][y] == -1.0 ) {
            unsigned int delta = 0;
            while ( block_seeds_color[x][y- delta] == -1.0)
                ++delta;
            size_t y_left = y - delta;
            delta = 0;
            while ( block_seeds_color[x][y + delta] == -1.0)
                ++delta;
            size_t y_right = y + delta;
            block_seeds_color[x][y] = linal_inteerpol( y_left, block_seeds_color[x][y_left] , y_right, block_seeds_color[x][y_right], y);
        }
    }
}

void perlin_noise:: get_board_const_y ( const unsigned int y, std::vector<std::vector<double> > &block_seeds_color ) {
    for ( size_t x = 0 ; x < size_screen_in_block_h; ++x ) {
        if ( block_seeds_color[x][y] == -1.0 ) {
            unsigned int delta = 0;
            while ( block_seeds_color[x - delta][y] == -1.0 )
                ++delta;
            size_t x_up = x - delta;
            delta = 0;
            while ( block_seeds_color[x+delta][y] == -1.0)
                ++delta;
            size_t x_down = x + delta;
            block_seeds_color[x][y] = linal_inteerpol( x_up, block_seeds_color[x_up][y] , x_down, block_seeds_color[x_down][y], x);
        }
    }
}

void  perlin_noise:: get_seed_color_for_board ( std::vector<std::vector<double> > &block_seeds_color ) 
{
    get_board_const_x( 0, block_seeds_color );
    get_board_const_x( size_screen_in_block_h - 1, block_seeds_color );
    get_board_const_y( 0, block_seeds_color );
    get_board_const_y( size_screen_in_block_w - 1, block_seeds_color );
}

void perlin_noise:: get_seed_color_for_all_elemantary_blocks ( std::vector<std::vector<double> > &block_seeds_color) 
{
    get_seed_color_for_board( block_seeds_color );
    for ( unsigned int  x = 0; x < size_screen_in_block_h; ++x )
        for ( unsigned int y = 0; y < size_screen_in_block_w; ++y ) {
            if ( block_seeds_color[x][y] == -1.0 )
                find_seed_color (x, y, block_seeds_color);
        }
}

void  perlin_noise:: generation ( std::vector<std::vector<double> > &block_seeds_color ) 
{
	srand(seed);
	size_screen_in_block_h = block_seeds_color.size();
	size_screen_in_block_w = block_seeds_color[0].size();

	perlin_noise:: set_node_generation( block_seeds_color );
	perlin_noise:: get_seed_color_for_all_elemantary_blocks ( block_seeds_color );
}