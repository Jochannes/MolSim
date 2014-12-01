/*
 * ForceCalculator_Gravity.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_GRAVITY_H_
#define FORCECALCULATOR_GRAVITY_H_


#include "ForceCalculator.h"
#include "Particle.h"


/**
 * \brief Class for calculating the gravitational force between two particles.
 */
class ForceCalculator_Gravity : public ForceCalculator
{
public:
	double g; //!< Acceleration coefficient.
	ForceCalculator_Gravity(double arg_g);
	virtual ~ForceCalculator_Gravity();

	virtual void compute(Particle& p);

	/**
	 * /brief Function for calculating the force between to particles.
	 *
	 * Since this is a non-interacting force, this method does nothing.
	 */
	virtual void compute(Particle& p1, Particle& p2) {}
};


#endif /* FORCECALCULATOR_GRAVITY_H_ */
