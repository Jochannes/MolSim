/*
 * ForceCalculator_Gravity.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Gravity.h"
#include "utils/Vector.h"

#include <cmath>

ForceCalculator_Gravity::ForceCalculator_Gravity(double arg_g) : g(arg_g) {
	ForceCalculator::interaction = false;
}

ForceCalculator_Gravity::~ForceCalculator_Gravity() {
}

/**
 * \brief Function for computing the gravitational force acting on one particle.
 *
 * @param p Accelerated particle.
 *
 * Calculates the gravitational force acting on a particle
 * and adds it to the overall force acting on that particle.
 * The force is calculated using the following equation:
 * \f[
 * G = m \cdot g_{\text{grav}}
 * \f]
 */
void ForceCalculator_Gravity::compute(Particle& p) {
	p.getF()[1] += p.getM() * g;
}

