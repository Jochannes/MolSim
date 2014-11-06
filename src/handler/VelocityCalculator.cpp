/*
 * VelocityCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "VelocityCalculator.h"
#include "global.h"

VelocityCalculator::VelocityCalculator() {
}

VelocityCalculator::~VelocityCalculator() {
}

void VelocityCalculator::compute(Particle& p) {
	double a = 0.5 * delta_t / p.getM();

	p.getV() = p.getV() + a * (p.getF() + p.getOldF());
}
