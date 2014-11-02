/*
 * PositionCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "PositionCalculator.h"


PositionCalculator::PositionCalculator() {
}


PositionCalculator::~PositionCalculator() {
}


/**
 * \brief Standard method for calculating the particle position.
 */
void PositionCalculator::compute(Particle& P)
{
	double a = 0.5 * delta_t * delta_t / P.getM();

	P.getX() = P.getX() + delta_t*P.getV() + a*P.getF();
}


