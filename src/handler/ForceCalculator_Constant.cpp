/*
 * ForceCalculator_Constant.cpp
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Constant.h"

using namespace std;
using namespace utils;


ForceCalculator_Constant::ForceCalculator_Constant(utils::Vector<double, 3> arg_force, int arg_type, double arg_start_time, double arg_end_time)
	: force(arg_force), type(arg_type), start_time(arg_start_time), end_time(arg_end_time) {
	ForceCalculator::interaction = false;
}

ForceCalculator_Constant::~ForceCalculator_Constant() {
}


/**
 * \brief Function for adding the force to a particle.
 *
 * Checks whether the particle has the right type.
 * If true, it applies the force to the particle.
 *
 * @param p Particle for which the force is added
 *
 */
void ForceCalculator_Constant::compute(Particle& p) {

	if( p.getType() == type ) {
		p.getF() = p.getF() + force;
	}
}

