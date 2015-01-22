/*
 * TemperatureAdjustHandler.h
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef TEMPERATUREADJUSTHANDLER_H_
#define TEMPERATUREADJUSTHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"

/**
 * \brief Class for adjusting the temperatures of all particles in a ParticleContainer.
 *
 */
class TemperatureAdjustHandler: public ParticleHandler
{
private:
	const double beta;		//!< Factor for scaling the velocities of the particles.
	const int direction;	//!< Id of the component for which the scaling is left out. -1 for none.
	const int type;			//!< Type of particle for which the temperature is adjusted.

public:
	TemperatureAdjustHandler(double param_beta, int arg_direction = -1, int arg_type = -1)
		: beta(param_beta), direction(arg_direction), type(arg_type)
	{ }

	virtual ~TemperatureAdjustHandler() {
	}

	/**
	 * \brief Method for adjusting the temperature of each particle.
	 *
	 * The new temperature is calculated by scaling the velocity with beta.
	 *
	 * @param p particle for which the new temperature is calculated.
	 */
	virtual void compute(Particle& p);
};


#endif /* TEMPERATUREADJUSTHANDLER_H_ */
