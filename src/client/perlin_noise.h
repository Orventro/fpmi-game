#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "consts.h"

class perlin_noise
{
public:
	perlin_noise ( time_t _seed,  unsigned int _step_node_h, unsigned int _step_node_w ) 
	{
		seed = _seed;
		rand_denominator = 10000;
		step_node_h = _step_node_h;
		step_node_w = _step_node_w;
	}

	~perlin_noise () 
	{

	}

	void generation ( std::vector<std::vector<double> > &block_seeds_color ) ;

private:	
	time_t seed;	
	unsigned int rand_denominator;
	unsigned int step_node_h;
	unsigned int step_node_w;

	unsigned int size_screen_in_block_h;
	unsigned int size_screen_in_block_w;

	double rand_double ();
	void set_node_generation ( std::vector<std::vector< double> > &block_seeds_color ) ;
	double linal_inteerpol ( unsigned int x1, const double y1, unsigned int x2, const double y2, unsigned int x);
	void find_seed_color ( const unsigned int x, const unsigned int y, std::vector<std::vector< double> > &block_seeds_color );
	void get_board_const_x ( const unsigned int x, std::vector<std::vector< double> > &block_seeds_color );
	void get_board_const_y ( const unsigned int y, std::vector<std::vector< double> > &block_seeds_color );
	void get_seed_color_for_board ( std::vector<std::vector< double> > &block_seeds_color );
	void get_seed_color_for_all_elemantary_blocks ( std::vector<std::vector< double> > &block_seeds_color );

};