/*
 * ForceCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_H_
#define FORCECALCULATOR_H_

#include "PairHandler.h"
#include "ParticleHandler.h"
#include "Particle.h"

/**
 * \brief Abstract class for defining the interface used for force calculation.
 *
 * This class defines the interface used for force calculation and therefore
 * enables the calculation method to be changed easily.
 * An inheriting function has to have a meaningful implementation of
 * either PairHandler::compute or ParticleHandler::compute, based
 * on the boolian value of interaction.
 */
class ForceCalculator: public PairHandler, public ParticleHandler {
public:
	ForceCalculator() {
	}

	virtual ~ForceCalculator() {
	}

	bool interaction; //!< Defines whether this force is a direct interaction between two particles.

	/**
	 * /brief Function for calculating the force between two particles.
	 */
	virtual void compute(Particle& p1, Particle& p2) = 0;

	/**
	 * /brief Function for calculating the force acting on one particle.
	 */
	virtual void compute(Particle& p) = 0;
};

#endif /* FORCECALCULATOR_H_ */
