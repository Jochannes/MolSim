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
#include <cmath>
#include <iostream>
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

	Particle P(pos, velocity, mass, type, epsilon, sigma);

	particleList.push_back(P);
}


void SphereGenerator::genRow(std::list<Particle>& particleList, int x, int y, int size)
{
	if(size < 0) {
		size = sqrt(radius*radius - x*x - y*y);
	}
	if (size > 0) {
		genParticle(particleList, x, y, 0);

		for(int i=1; i<=size; i++) {
			genParticle(particleList, x, y, i);
			genParticle(particleList, x, y, -i);
		}
	}
}


void SphereGenerator::genCircle(std::list<Particle>& particleList)
{
	LOG4CXX_DEBUG(SGLogger, "generating sphere " << toString());

	int r_2 = radius*radius;
	int y = radius;

	// center
	genParticle(particleList, 0, 0, 0);

	// cross
	for(int i=1; i<radius; i++) {
		genParticle(particleList, 0, i, 0);
		genParticle(particleList, 0, -i, 0);
		genParticle(particleList, i, 0, 0);
		genParticle(particleList, -i, 0, 0);
	}

	// rest of circle
	for(int x=1; x<y; x++) {

		if( (x*x + y*y) > r_2 ) {
			y--;
		}

		// diagonale
		genParticle(particleList, x, x, 0);
		genParticle(particleList, x, -x, 0);
		genParticle(particleList, -x, x, 0);
		genParticle(particleList, -x, -x, 0);

		// plot rows
		for(int i=x+1; i<=y; i++) {

			genParticle(particleList, x, i, 0);
			genParticle(particleList, i, x, 0);

			genParticle(particleList, x, -i, 0);
			genParticle(particleList, i, -x, 0);

			genParticle(particleList, -x, i, 0);
			genParticle(particleList, -i, x, 0);

			genParticle(particleList, -x, -i, 0);
			genParticle(particleList, -i, -x, 0);
		}
	}
}


void SphereGenerator::genSphere(std::list<Particle>& particleList)
{
	LOG4CXX_DEBUG(SGLogger, "generating sphere " << toString());

	int r_2 = radius*radius;
	int y = radius;

	// center
	genRow(particleList, 0, 0, radius-1);

	// cross
	for(int i=1; i<radius; i++) {
		genRow(particleList, 0, i);
		genRow(particleList, 0, -i);
		genRow(particleList, i, 0);
		genRow(particleList, -i, 0);
	}

	// rest of circle
	for(int x=1; x<y; x++) {

		if( (x*x + y*y) > r_2 ) {
			y--;
		}

		// diagonale
		genRow(particleList, x, x);
		genRow(particleList, x, -x);
		genRow(particleList, -x, x);
		genRow(particleList, -x, -x);

		// plot rows
		for(int i=x+1; i<=y; i++) {

			genRow(particleList, x, i);
			genRow(particleList, i, x);

			genRow(particleList, x, -i);
			genRow(particleList, i, -x);

			genRow(particleList, -x, i);
			genRow(particleList, -i, x);

			genRow(particleList, -x, -i);
			genRow(particleList, -i, -x);
		}
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
			"; type=" << type <<
			"; epsilon=" << epsilon <<
			"; sigma=" << sigma <<
			"; mode=" << (use3D ? "3D" : "2D") <<
			"]";

	return str.str();
}

/**
 * \brief Generate a sphere or circle.
 *
 * Generates a sphere or circle of particles in a grid
 * using the parameters specified in the constructor.
 *
 * @param particleList List of particles to store the generated particles.
 */
void SphereGenerator::input(std::list<Particle>& particleList) {
	if(use3D)
		genSphere(particleList);
	else
		genCircle(particleList);
}
