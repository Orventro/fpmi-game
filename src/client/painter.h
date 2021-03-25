#pragma once

#include <vector>

class painter
{
public:
	painter( size_t _board_water, size_t _board_sand, std::vector<std::vector<double> > &block_seeds_color ) 
	{
		board_water = _board_water;
		board_sand = _board_sand;
		size_screen_in_block_h = block_seeds_color.size();
		size_screen_in_block_w = block_seeds_color[0].size();
	}

	void set_type_block (  std::vector<std::vector<double> > &block_seeds_color , std::vector<std::vector<unsigned int> > &type_block ) ;

	void get_distance_neighborhood_biom ( std::vector<std::vector<unsigned int> > &type_block, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom);

	~painter() 
	{

	}
	
private:
	size_t board_water;
	size_t board_sand;	

	size_t size_screen_in_block_h;
	size_t size_screen_in_block_w;

	bool check_neighborhood ( unsigned int x, unsigned int y, std::vector<std::vector<unsigned int> > &type_block );
	void get_board_bioms ( std::vector<std::vector<unsigned int> > &type_block, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom);
	bool check_neighborhood_distance ( unsigned int x, unsigned int y, unsigned int d, std::vector<std::vector< unsigned int> > &distance_neighborhood_biom ) ;

 /*
	void get_board_bioms ( std::vector<std::vector< unsigned int> > &distance_neighborhood_biom );
	bool check_neighborhood_distance ( unsigned int x, unsigned int y, unsigned int d , std::vector<std::vector< unsigned int> > &distance_neighborhood_biom ) ;
	bool check_neighborhood ( unsigned int x, unsigned int y, std::vector<std::vector<unsigned int> > &type_block );
	*/
};