/*
 * PositionCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "PositionCalculator.h"
#include "global.h"


PositionCalculator::PositionCalculator() {
}


PositionCalculator::~PositionCalculator() {
}


void PositionCalculator::compute(Particle& P)
{
	double a = 0.5 * delta_t * delta_t / P.getM();

	P.getX() = P.getX() + delta_t*P.getV() + a*P.getF();
}


