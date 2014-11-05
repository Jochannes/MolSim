/*
 * VelocityCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef VELOCITYCALCULATOR_H_
#define VELOCITYCALCULATOR_H_

#include "ParticleHandler.h"


/**
 * \brief Class for defining the interface used for velocity calculation.
 *
 * This class defines the inteface used for velocity calculation and therefore
 * enables the calculation method to be changed easily.
 */
class VelocityCalculator : public ParticleHandler
{
public:
	VelocityCalculator();
	virtual ~VelocityCalculator();

	virtual void compute(Particle& P);
};


#endif /* VELOCITYCALCULATOR_H_ */
