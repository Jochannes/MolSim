/*
 * SphereGenerator.cpp
 *
 *  Created on: 25.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "SphereGenerator.h"
#include "MaxwellBoltzmannDistribution.h"
#include "utils/Vector.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;

LoggerPtr SGLogger(Logger::getLogger("MolSim.ParticleInput.SphereGenerator"));


void SphereGenerator::genParticle(std::list<Particle>& particleList, int x, int y, int z)
{
	utils::Vector<double, 3> pos;
	pos[0] = center_position[0] + x*distance;
	pos[1] = center_position[1] + y*distance;
	pos[2] = center_position[2] + z*distance;

	Particle P(pos, velocity, mass);
	MaxwellBoltzmannDistribution(P, brown_factor, 3);

	particleList.push_back(P);
}


void SphereGenerator::genCircle(std::list<Particle>& particleList, int r, int z)
{
	int r_2 = r*r;
	int y = r;
/*
	// cross
	for(int i=0; i<r; i++) {
		genParticle(particleList, 0, i, z);
		genParticle(particleList, 0, -i, z);
		genParticle(particleList, i, 0, z);
		genParticle(particleList, -i, 0, z);
	}
*/
	// rest of circle
	for(int x=1; x<y; x++) {

		if( (x*x + y*y) > r_2 ) {
			y--;
		}

		// diagonale
		genParticle(particleList, x, x, z);
		genParticle(particleList, x, -x, z);
		genParticle(particleList, -x, x, z);
		genParticle(particleList, -x, -x, z);

		// plot rows
		for(int i=x+1; i<=y; i++) {
			genParticle(particleList, x, i, z);
			genParticle(particleList, i, x, z);

			genParticle(particleList, x, -i, z);
			genParticle(particleList, i, -x, z);

			genParticle(particleList, -x, i, z);
			genParticle(particleList, -i, x, z);

			genParticle(particleList, -x, -i, z);
			genParticle(particleList, -i, -x, z);
		}


	}
}

void SphereGenerator::input(std::list<Particle>& particleList)
{
	LOG4CXX_DEBUG(SGLogger, "generating sphere " << toString());

	int r_2 = (radius-1)*(radius-1);
	int y = radius-1;

	// center
	genCircle(particleList, radius, 0);

	// rest of sphere
	for(int z=1; z<y; z++) {

		if( (z*z + y*y) > r_2 ) {
			y--;
		}

		genCircle(particleList, y, z);
		genCircle(particleList, y, -z);

		genCircle(particleList, radius-y, z);
		genCircle(particleList, radius-y, -z);
	}
}


std::string SphereGenerator::toString()
{
	std::stringstream str;

	str <<	"[x=" << center_position.toString() <<
			"; r=" << radius <<
			"; h=" << distance <<
			"; m=" << mass <<
			"; v=" << velocity.toString() <<
			"; brown_factor=" << brown_factor <<
			"]";

	return str.str();
}
