/*
 * PositionCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "PositionCalculator.h"


// global variable for calculation. See "src/global.h".
extern double delta_t;


PositionCalculator::PositionCalculator() {
}

PositionCalculator::~PositionCalculator() {
}

void PositionCalculator::compute(Particle& p) {
	double a = 0.5 * delta_t * delta_t / p.getM();

	p.getX() = p.getX() + delta_t * p.getV() + a * p.getF();
}

