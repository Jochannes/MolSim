/*
 * ForceCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_H_
#define FORCECALCULATOR_H_

#include "../PairHandler.h"


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

	virtual void compute(Particle& P1, Particle& P2) = 0;
};


#endif /* FORCECALCULATOR_H_ */
