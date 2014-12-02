/*
 * MaxwellBoltzmannHandler.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "MaxwellBoltzmannHandler.h"
#include "MaxwellBoltzmannDistribution.h"


void MaxwellBoltzmannHandler::compute(Particle& p)
{
	MaxwellBoltzmannDistribution(p, meanVelocity, num_dimensions);
}
