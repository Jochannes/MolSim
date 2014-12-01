/*
 * ForceCalculatorLennardJones.h
 *
 *  Created on: Oct 30, 2014
 *      Author: johannes
 */

#ifndef FORCECALCULATORLENNARDJONES_H_
#define FORCECALCULATORLENNARDJONES_H_

#include "ForceCalculator.h"
#include "Particle.h"
/**
 * \brief Class for calculating the force between two particles caused by the Lennard-Jones potential.
 */
class ForceCalculator_LennardJones: public ForceCalculator {
public:
	ForceCalculator_LennardJones();

	virtual ~ForceCalculator_LennardJones();

	virtual void compute(Particle& p1, Particle& p2);

	/**
	 * /brief Function for calculating the force acting on one particle.
	 *
	 * Since this is an interaction force, this method does nothing.
	 */
	virtual void compute(Particle& p) {}
};

#endif /* FORCECALCULATORLENNARDJONES_H_ */
