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
	static const double sigma = 1;		//!< Sigma value used for the potential (see equation)
	static const double epsilon = 5;	//!< Epsilon value used for the potential (see equation)

	ForceCalculator_LennardJones();
	virtual ~ForceCalculator_LennardJones();

	virtual void compute(Particle& p1, Particle& p2);
};

#endif /* FORCECALCULATORLENNARDJONES_H_ */
