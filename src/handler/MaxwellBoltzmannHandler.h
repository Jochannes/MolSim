/*
 * MaxwellBoltzmannHandler.h
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef MAXWELLBOLTZMANNHANDLER_H_
#define MAXWELLBOLTZMANNHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"

/**
 * \brief Class for adding brownian motion to all particles in a ParticleContainer.
 *
 */
class MaxwellBoltzmannHandler: public ParticleHandler
{
private:
	const double meanVelocity;		//!< mean velocity of the brownian motion for the particle
	const int    num_dimensions;	//!< number of dimensions (2 or 3)

public:
	MaxwellBoltzmannHandler(double param_meanVelocity, int param_num_dimensions) :
		meanVelocity(param_meanVelocity), num_dimensions(param_num_dimensions)
	{ }

	virtual ~MaxwellBoltzmannHandler() {
	}

	/**
	 * \brief Method for applying the brownian motion to each particle.
	 *
	 * @param p particle to initialize.
	 */
	virtual void compute(Particle& p);
};


#endif /* MAXWELLBOLTZMANNHANDLER_H_ */
