/*
 * ForceCalculatorLennardJones.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: johannes
 */

#include "ForceCalculator_LennardJones.h"
#include "utils/Vector.h"

#include <cmath>

using namespace utils;


ForceCalculator_LennardJones::ForceCalculator_LennardJones(double arg_cutoff) :
		cutoff_factor(arg_cutoff), cutoff_factor2(arg_cutoff * arg_cutoff) {
	ForceCalculator::interaction = true;
}

ForceCalculator_LennardJones::~ForceCalculator_LennardJones() {
}

/**
 * \brief Function for computing the forces caused by the Lennard-Jones potential.
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
void ForceCalculator_LennardJones::compute(Particle& p1, Particle& p2) {

	//Calculate epsilon and sigma
	double epsilon, sigma2;
	if (p1.getType() == p2.getType()) {
		epsilon = p1.getEpsilon();
		sigma2 = pow(p1.getSigma(), 2);
	} else {
		epsilon = sqrt(p1.getEpsilon() * p2.getEpsilon());
		sigma2 = pow((p1.getSigma() + p2.getSigma()) * 0.5, 2);
	}

	Vector<double, 3> xdiff = p2.getX() - p1.getX();
	double cutoff2 = cutoff_factor2 * sigma2;
	double distance2 = xdiff.L2Norm2();

	if (distance2 < cutoff2 || cutoff2 == 0) {
		double invDistance2 = 1.0 / distance2;

		double factor = pow(sigma2 * invDistance2, 3);
		factor *= 1 - 2 * factor;
		factor *= 24 * epsilon * invDistance2;

		Vector<double, 3> force = factor * xdiff;

		p1.getF() = p1.getF() + force;
		p2.getF() = p2.getF() - force; // according to Newton's third law: F_P1 = -F_P2
	}
}

