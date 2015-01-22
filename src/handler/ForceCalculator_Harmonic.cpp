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
	ForceCalculator::interaction = false;
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
}


/**
 * \brief Function for adding the (harmonic) interaction with its neighbors to a particle.
 *
 * @param p Particle for which the force is calculated
 *
 */
void ForceCalculator_Harmonic::compute(Particle& p) {

	for(int i=0; i<8; i++) {
		Particle* neighbor = p.getNeighbor(i);

		if( neighbor != NULL ) {
			if( (i%2) == 0 )
				calc_diag(p, *neighbor);
			else
				calc_direct(p, *neighbor);
		}
	}
}


