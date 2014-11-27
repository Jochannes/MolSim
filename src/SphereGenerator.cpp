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

void SphereGenerator::input(std::list<Particle>& particleList)
{
	LOG4CXX_DEBUG(SGLogger, "generating sphere " << toString());

	// TODO: produce sphere
	
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
