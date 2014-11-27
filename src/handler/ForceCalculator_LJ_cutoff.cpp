/*
 * ForceCalculator_LJ_cutoff.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: johannes
 */

#include "ForceCalculator_LJ_cutoff.h"
#include "ForceCalculator_LennardJones.h"
#include "utils/Vector.h"

#include <cmath>

ForceCalculator_LJ_cutoff::ForceCalculator_LJ_cutoff() :
		cutoff(3.0) {
}

ForceCalculator_LJ_cutoff::~ForceCalculator_LJ_cutoff() {
}

/**
 * \brief Computes the forces caused by the Lennard-Jones potential, if the particles are closer than cutoff.
 * @param p1 First interacting particle (at \f$ x_i \f$ )
 * @param p2 Second interacting particle (at \f$ x_j \f$ )
 *
 * If the particles are closer than cutoff, this method calculates the
 * forces between two particles caused by the Lennard-Jones potential
 * and adds it to the force acting on both particles.
 * The force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{24 \cdot \epsilon}{\left( \left\| x_i - x_j \right\|_2 \right)^2} \cdot
 * \left( \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^6 - 2 \cdot \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^{12} \right)
 * \cdot \left( x_j - x_i \right)
 * \f]
 */
void ForceCalculator_LJ_cutoff::compute(Particle& p1, Particle& p2) {
	double distance = (p1.getX() - p2.getX()).L2Norm();
	if (distance < cutoff) {
		double invDistance = 1.0 / distance;

		double factor = 24 * ForceCalculator_LennardJones::epsilon * invDistance
				* invDistance
				* (pow(ForceCalculator_LennardJones::sigma * invDistance, 6)
						- 2
								* pow(
										ForceCalculator_LennardJones::sigma
												* invDistance, 12));

		utils::Vector<double, 3> force = factor * (p2.getX() - p1.getX());

		p1.getF() = p1.getF() + force;
		p2.getF() = p2.getF() - force; // according to Newton's third law: F_P1 = -F_P2
	}
}

