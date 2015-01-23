/*
 * ForceCalculator_Harmonic.cpp
 *
 *  Created on: 22.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Harmonic.h"
#include "utils/Vector.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;
using namespace utils;


ForceCalculator_Harmonic::ForceCalculator_Harmonic(double arg_k, double arg_r) : k(arg_k), r(arg_r) {
	ForceCalculator::interaction = true;
}

ForceCalculator_Harmonic::~ForceCalculator_Harmonic() {
}


/**
 * /brief Auxiliary function for adding the (harmonic) interaction between direct neighbors.
 *
 * @param p1 Particle for which the force is calculated
 * @param p2 A direct neighbor of the first particle
 */
void ForceCalculator_Harmonic::calc_direct(Particle& p1, Particle& p2)
{
	Vector<double, 3> diff_x = p2.getX() - p1.getX();

	Vector<double, 3> force = diff_x * k * (1.0 - r/diff_x.L2Norm());

	p1.getF() = p1.getF() + force;
	p2.getF() = p2.getF() - force;
}


/**
 * /brief Auxiliary function for adding the (harmonic) interaction between diagonal neighbors.
 *
 * @param p1 Particle for which the force is calculated
 * @param p2 A diagonal neighbor of the first particle
 */
void ForceCalculator_Harmonic::calc_diag(Particle& p1, Particle& p2)
{
	Vector<double, 3> diff_x = p2.getX() - p1.getX();

	Vector<double, 3> force = diff_x * k * (1.0 - M_SQRT2*r/diff_x.L2Norm());

	p1.getF() = p1.getF() + force;
	p2.getF() = p2.getF() - force;
}


/**
 * \brief Function for adding the (harmonic) interaction, if the particles are neighbors.
 *
 * @param p First particle of the particle pair.
 * @param p Other particle of the particle pair.
 */
void ForceCalculator_Harmonic::compute(Particle& p1, Particle& p2) {

	if( p1.isDiagNeighbor(p2) ) {
		calc_diag(p1, p2);
	}
	else if( p1.isDirectNeighbor(p2) ) {
		calc_direct(p1, p2);
	}
}


