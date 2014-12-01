/*
 * ForceCalculator_LJ_cutoff.h
 *
 *  Created on: Nov 27, 2014
 *      Author: johannes
 */

#ifndef FORCECALCULATOR_LJ_CUTOFF_H_
#define FORCECALCULATOR_LJ_CUTOFF_H_

#include "ForceCalculator.h"
#include "Particle.h"

/**
 * \brief Class for calculating the force caused by the Lennard-Jones potential with cutoff radius.
 */
class ForceCalculator_LJ_cutoff: public ForceCalculator {
public:
	double cutoff_factor; //!< Multiple of sigma at which the interaction starts.

	ForceCalculator_LJ_cutoff(double arg_cutoff);

	virtual ~ForceCalculator_LJ_cutoff();

	virtual void compute(Particle& p1, Particle& p2);

	/**
	 * /brief Function for calculating the force acting on one particle.
	 *
	 * Since this is an interaction force, this method does nothing.
	 */
	virtual void compute(Particle& p) {}
};

#endif /* FORCECALCULATOR_LJ_CUTOFF_H_ */
