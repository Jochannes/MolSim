/*
 * MembraneGenerator.cpp
 *
 *  Created on: 22.12.2014
 *      Author: Jochannes, DanielCAlbert
 */


#include "MembraneGenerator.h"
#include "Particle.h"
#include "utils/Vector.h"

#include <cstdlib>
#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;

LoggerPtr MGLogger(Logger::getLogger("MolSim.ParticleInput.MembraneGenerator"));


void MembraneGenerator::input(list<Particle>& particleList)
{
	LOG4CXX_DEBUG(MGLogger, "generating membrane " << toString());

	Particle* m[num_particles[0]][num_particles[1]];		// grid for accessing the particles

	utils::Vector<double, 3> x;
	x[0] = corner_position[0];		// set first coordinate


	// generate the particles
	for(int i=0; i < num_particles[0]; i++) {
		x[1] = corner_position[1];		// reset second coordinate

		for (int j=0; j < num_particles[1]; j++) {
			// create a new Particle, add to grid
			Particle p(x, velocity, mass, type, epsilon, sigma);
			particleList.push_back(p);
			m[i][j] = &(particleList.back());

			x[1] = x[1] + distance;
		}
		x[0] = x[0] + distance;
	}

	// change the type of the marked particles
	if( mark_pos_x >= 0  &&  mark_pos_x < num_particles[0]  &&
		mark_pos_y >= 0  &&  mark_pos_y < num_particles[1] )
	{
		m[mark_pos_x][mark_pos_y]->setType(mark_type);

		if( mark_pos_x+1 < num_particles[0] ) {
			m[mark_pos_x+1][mark_pos_y]->setType(mark_type);

			if( mark_pos_y+1 < num_particles[1] ) {
				m[mark_pos_x][mark_pos_y+1]->setType(mark_type);
				m[mark_pos_x+1][mark_pos_y+1]->setType(mark_type);
			}
		}
		else {
			if( mark_pos_y+1 < num_particles[1] ) {
				m[mark_pos_x][mark_pos_y+1]->setType(mark_type);
			}
		}
	}
}


std::string MembraneGenerator::toString()
{
	std::stringstream str;

	str <<	"[x=" << corner_position.toString() <<
			"; n=[" << num_particles[0] << "," << num_particles[1] << "," << num_particles[2] << "]" <<
			"; h=" << distance <<
			"; m=" << mass <<
			"; v=" << velocity.toString() <<
			"; type=" << type <<
			"; epsilon=" << epsilon <<
			"; sigma=" << sigma <<
			"; mark=[type=" << mark_type << ",x=" << mark_pos_x << ",y=" << mark_pos_y << "]" <<
			"]";

	return str.str();
}

