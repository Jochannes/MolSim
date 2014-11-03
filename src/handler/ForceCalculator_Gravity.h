/*
 * ForceCalculator_Gravity.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_GRAVITY_H_
#define FORCECALCULATOR_GRAVITY_H_


#include "ForceCalculator.h"
#include "../Particle.h"
#include "../utils/Vector.h"
#include "../global.h"


/**
 * \brief Class for calculating the gravitational force between two particles.
 */
class ForceCalculator_Gravity : public ForceCalculator
{
public:
	ForceCalculator_Gravity();
	virtual ~ForceCalculator_Gravity();

	virtual void compute(Particle& P1, Particle& P2);
};


#endif /* FORCECALCULATOR_GRAVITY_H_ */
