/*
 * VelocityCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "VelocityCalculator.h"
#include "../Particle.h"
#include "../global.h"


VelocityCalculator::VelocityCalculator() {
}


VelocityCalculator::~VelocityCalculator() {
}

/**
 * \brief Standard method for calculating the particle velocity.
 */
void VelocityCalculator::compute(Particle& P)
{
	double a = 0.5 * delta_t / P.getM();

	P.getV() = P.getV() + a * (P.getF() + P.getOldF());
}
