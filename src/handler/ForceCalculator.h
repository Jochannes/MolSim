/*
 * ForceCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_H_
#define FORCECALCULATOR_H_

#include "PairHandler.h"
#include "Particle.h"


/**
 * \brief Abstract class for defining the interface used for force calculation.
 *
 * This class defines the inteface used for force calculation and therefore
 * enables the calculation method to be changed easily.
 */
class ForceCalculator : public PairHandler
{
public:
	ForceCalculator() {
	}

	virtual ~ForceCalculator() {
	}

	/**
	 * /brief Abstract function for calculating the force between to particles.
	 */
	virtual void compute(Particle& p1, Particle& p2) = 0;
};


#endif /* FORCECALCULATOR_H_ */
