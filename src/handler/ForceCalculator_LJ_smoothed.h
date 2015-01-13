/*
 * ForceCalculatorLJsmoothed.h
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#ifndef FORCECALCULATORLJSMOOTHED_H_
#define FORCECALCULATORLJSMOOTHED_H_

#include "ForceCalculator.h"
#include "Particle.h"

#include <vector>

/**
 * \brief Class for calculating the force between two particles caused by the Lennard-Jones potential.
 */
class ForceCalculator_LJ_smoothed: public ForceCalculator {
private:
	double cutoff_factor2; //!< Squared cutoff_factor.
	double rl2;	//!< Squared rl.

public:
	double cutoff_factor; //!< Multiple of sigma at which the interaction starts. 0 if no cutoff is used.
	double rl;	//!< Radius determining the area in which the force is smoothed.

	ForceCalculator_LJ_smoothed(double arg_cutoff, double arg_rl);

	virtual ~ForceCalculator_LJ_smoothed();

	virtual void compute(Particle& p1, Particle& p2);

	/**
	 * /brief Function for calculating the force acting on one particle.
	 *
	 * Since this is an interaction force, this method does nothing.
	 */
	virtual void compute(Particle& p) {}
};

#endif /* FORCECALCULATORLJSMOOTHED_H_ */
