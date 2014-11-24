/*
 * ForceCalculatorLennardJones.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: johannes
 */

#include "ForceCalculator_LennardJones.h"
#include "utils/Vector.h"

#include <cmath>

ForceCalculator_LennardJones::ForceCalculator_LennardJones() {
}

ForceCalculator_LennardJones::~ForceCalculator_LennardJones() {
}

/**
 * \brief Function for computing the forces caused by the Lennard-Jones potential.
 * @param p1 First interacting particle (at \f$ x_i \f$ )
 * @param p2 Second interacting particle (at \f$ x_j \f$ )
 *
 * Calculates the forces between two particles caused by the Lennard-Jones potential
 * and adds it to the force acting on the first particle.
 * The force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{24 \cdot \epsilon}{\left( \left\| x_i - x_j \right\|_2 \right)^2} \cdot
 * \left( \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^6 - 2 \cdot \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^{12} \right)
 * \cdot \left( x_j - x_i \right)
 * \f]
 */
void ForceCalculator_LennardJones::compute(Particle& p1, Particle& p2) {
	double invDistance = 1.0 / (p1.getX() - p2.getX()).L2Norm();

	double factor = 24 * epsilon * invDistance * invDistance *
				(pow(sigma * invDistance, 6) - 2 * pow(sigma * invDistance, 12));

	utils::Vector<double, 3> force = factor * (p2.getX() - p1.getX());

	p1.getF() = p1.getF() + force;
	p2.getF() = p2.getF() - force;	// according to Newton's third law: F_P1 = -F_P2
}

