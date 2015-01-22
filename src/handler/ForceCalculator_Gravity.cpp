/*
 * ForceCalculator_Gravity.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Gravity.h"
#include "utils/Vector.h"

#include <cmath>

ForceCalculator_Gravity::ForceCalculator_Gravity(double arg_g, unsigned int arg_direction, int arg_type)
	: g(arg_g), direction(arg_direction), type(arg_type) {
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
 *
 * The force is only calculated if the particle's type matches
 * the one specified in 'type' member variable. If 'type' is -1,
 * the force is always applied.
 */
void ForceCalculator_Gravity::compute(Particle& p) {

	if( type == -1  ||  p.getType() == type) {
		p.getF()[direction] += p.getM() * g;
	}
}

