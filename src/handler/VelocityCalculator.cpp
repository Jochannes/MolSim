/*
 * VelocityCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "VelocityCalculator.h"


// global variable for calculation. See "src/global.h".
extern double delta_t;


VelocityCalculator::VelocityCalculator() {
}

VelocityCalculator::~VelocityCalculator() {
}

void VelocityCalculator::compute(Particle& p) {
	double a = 0.5 * delta_t / p.getM();

	p.getV() = p.getV() + a * (p.getF() + p.getOldF());
}
