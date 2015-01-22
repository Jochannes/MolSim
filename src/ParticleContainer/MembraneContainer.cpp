/*
 * MembraneContainer.h
 *
 *  Created on: 22.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#include "MembraneContainer.h"
#include <list>

using namespace std;
using namespace utils;

/**
 * \brief Adds a list of particles arranged in a 2D grid to the container.
 * The list has to store the particles in the right order:
 * (0,0), (0,1), (0,2), ... (1,0), (1,1), (1,2), ...
 * This is the recommended way of initializing this container
 * since it also sets the neighbor attributes correctly.
 *
 * @param p The list of particles
 */
void MembraneContainer::fill_grid(list<Particle>& grid_list, int size_x, int size_y) {

	Particle* m[size_x][size_y];		// grid for accessing the particles
	int x = 0, y = 0;

	// allocate space for cells
	reserve( size_x * size_y );

	// add the particles to the container
	for( list<Particle>::iterator it = grid_list.begin();
		 it != grid_list.end();
		 it++ )
	{
		m[x][y] = add(*it);		// store the pointer to the added particle

		x++;
		if( x == size_x ) {
			x = 0;
			y++;
		}
	}

	// set the neighbors
	for(int i=0; i<size_x; i++) {
		for (int j = 0; j < size_y; j++) {

			if( (i-1)>0 && (j+1)<size_y ) {
				m[i][j]->setNeighbor(0, *m[i-1][j+1]);	// upper-left
			}
			if( (j+1)<size_y ) {
				m[i][j]->setNeighbor(1, *m[i][j+1]);		// upper
			}
			if( (i+1)<size_x && (j+1)<size_y ) {
				m[i][j]->setNeighbor(2, *m[i+1][j+1]);	// upper-right
			}
			if( (i+1)<size_x ) {
				m[i][j]->setNeighbor(3, *m[i+1][j]);		// right
			}
			if( (i+1)<size_x && (j-1)>0 ) {
				m[i][j]->setNeighbor(4, *m[i+1][j-1]);	// lower-right
			}
			if( (j-1)>0 ) {
				m[i][j]->setNeighbor(5, *m[i][j-1]);		// lower
			}
			if( (i-1)>0 && (j-1)>0 ) {
				m[i][j]->setNeighbor(6, *m[i-1][j-1]);	// lower-left
			}
			if( (i-1)>0 ) {
				m[i][j]->setNeighbor(7, *m[i-1][j]);		// left
			}
		}
	}



}

