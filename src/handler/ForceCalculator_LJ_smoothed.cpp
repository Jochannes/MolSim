/*
 * ForceCalculatorLJsmoothed.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#include "ForceCalculator_LJ_smoothed.h"
#include "utils/Vector.h"

#include <cmath>

using namespace utils;


ForceCalculator_LJ_smoothed::ForceCalculator_LJ_smoothed(double arg_cutoff, double arg_rl) :
		cutoff_factor(arg_cutoff), cutoff_factor2(arg_cutoff * arg_cutoff), rl(arg_rl), rl2(arg_rl * arg_rl) {
	ForceCalculator::interaction = true;
}

ForceCalculator_LJ_smoothed::~ForceCalculator_LJ_smoothed() {
}

/**
 * \brief Function for computing the forces caused by the smoothed Lennard-Jones potential.
 * @param p1 First interacting particle (at \f$ x_i \f$ )
 * @param p2 Second interacting particle (at \f$ x_j \f$ )
 *
 * This method calculates the forces between two particles
 * caused by the smoothed Lennard-Jones potential and adds
 * it to the force acting on both particles.
 * The force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{24 \cdot \epsilon \cdot S_{ij}}{\left( \left\| x_i - x_j \right\|_2 \right)^2} \cdot
 * \left( \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^6 - 2 \cdot \left( \frac{\sigma}{\left\| x_i - x_j \right\|_2} \right)^{12} \right)
 * \cdot \left( x_j - x_i \right)
 * \f]
 * with
 * \f[
 * S_{ij} = \begin{cases} 1 &\mbox{if } \left| x_i - x_j \right\|_2 \le r_l \\
 * 		1 - \left( \left| x_i - x_j \right\|_2 - r_l \right) ^2 \cdot \frac{3 r_{\mbox{cutoff}} - r_l - 2 \left| x_i - x_j \right\|_2}{\left( r_{\mbox{cutoff}} - r_l \right)^3}
 * 			&\mbox{if } r_l < \left| x_i - x_j \right\|_2 < r_{\mbox{cutoff}}\\
 * 		0 &\mbox{if } \left| x_i - x_j \right\|_2 \ge r_{\mbox{cutoff}}. \end{cases}
 * \f]
 */
void ForceCalculator_LJ_smoothed::compute(Particle& p1, Particle& p2) {

	//Calculate epsilon and sigma
	double epsilon, sigma, sigma2;
	if (p1.getType() == p2.getType()) {
		epsilon = p1.getEpsilon();
		sigma = p1.getSigma();
	} else {
		epsilon = sqrt(p1.getEpsilon() * p2.getEpsilon());
		sigma = (p1.getSigma() + p2.getSigma()) * 0.5;
	}
	sigma2 = sigma * sigma;

	Vector<double, 3> diff_force = p2.getX() - p1.getX();
	double cutoff2 = cutoff_factor2 * sigma2;
	double distance2 = diff_force.L2Norm2();

	if (distance2 < cutoff2 || cutoff2 == 0) {
		double invDistance2 = 1.0 / distance2;

		double factor = pow(sigma2 * invDistance2, 3);
		factor *= 1 - 2 * factor;
		factor *= 24 * epsilon * invDistance2;

		//Smoothed area
		if(distance2 > rl2){
			double distance = sqrt(distance2);
			double cutoff = sigma * cutoff_factor;
			double smFactor = (3*cutoff - rl - 2*distance) / pow(cutoff - rl, 3);
			smFactor *= pow(distance - rl, 2);
			factor -= smFactor;
		}

		diff_force = factor * diff_force;

		p1.getF() = p1.getF() + diff_force;
		p2.getF() = p2.getF() - diff_force; // according to Newton's third law: F_P1 = -F_P2
	}
}

