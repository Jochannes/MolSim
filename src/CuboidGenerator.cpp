/*
 * CuboidGenerator.cpp
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "CuboidGenerator.h"
#include "MaxwellBoltzmannDistribution.h"
#include "utils/Vector.h"

#include <cstdlib>
#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;

LoggerPtr CGLogger(Logger::getLogger("MolSim.ParticleInput.CuboidGenerator"));


void CuboidGenerator::input(list<Particle>& particleList)
{
	LOG4CXX_DEBUG(CGLogger, "generating cuboid " << toString());

	utils::Vector<double, 3> x;
	x[0] = corner_position[0];		// set first coordinate

	for (int i = 0; i < num_particles[0]; i++) {
		x[1] = corner_position[1];		// reset second coordinate

		for (int j = 0; j < num_particles[1]; j++) {
			x[2] = corner_position[2];		// reset third coordinate

			for (int k = 0; k < num_particles[2]; k++) {
				// create a new Particle
				Particle p(x, velocity, mass);

				// add brownian motion
				if (num_particles[2] == 1) {
					MaxwellBoltzmannDistribution(p, brown_factor, 2);
				} else {
					MaxwellBoltzmannDistribution(p, brown_factor, 3);
				}

				// add particle to the passed particle list
				particleList.push_back(p);

				x[2] = x[2] + distance;
			}
			x[1] = x[1] + distance;
		}
		x[0] = x[0] + distance;
	}
}


std::string CuboidGenerator::toString()
{
	std::stringstream str;

	str <<	"[x=" << corner_position.toString() <<
			"; n=[" << num_particles[0] << "," << num_particles[1] << "," << num_particles[2] <<
			"]; h=" << distance <<
			"; m=" << mass <<
			"; v=" << velocity.toString() <<
			"; brown_factor=" << brown_factor <<
			"]";

	return str.str();
}

