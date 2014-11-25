/*
 * ReflectionHandler.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef REFLECTIONHANDLER_H_
#define REFLECTIONHANDLER_H_

#include "ParticleContainer/SimpleContainer.h"

/**
 * \brief Handler for reflecting particles from the domain border.
 *
 * This class is designed specifically for the Lennard-Jones-Potential.
 */
class ReflectionHandler: public ParticleHandler {
public:
	ReflectionHandler();
	virtual ~ReflectionHandler();

	/**
	 * \brief Integer defining the domain side on which this condition is imposed.
	 *
	 * The domain sides are defined as following:
	 * 0: x=0
	 * 1: x=max
	 * 2: y=0
	 * 3: y=max
	 * 4: z=0
	 * 5: z=max
	 */
	int side;
	SimpleContainer* cont; //<! Particle container from which sides the particle is reflected.

	virtual void compute(Particle& p);
};

#endif /* REFLECTIONHANDLER_H_ */
