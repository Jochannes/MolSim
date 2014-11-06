/*
 * ParticleHandler.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEHANDLER_H_
#define PARTICLEHANDLER_H_

#include "Particle.h"


/**
 * \brief Abstract class for defining an interface
 *        for processing a particle when iterating
 *        over a particle container
 */
class ParticleHandler
{
public:
	ParticleHandler() {
	}

	virtual ~ParticleHandler() {
	}

	/*
	 * function to execute for each particle.
	 *
* @param P The particle to process
	 */
	virtual void compute(Particle& P) = 0;

};


#endif /* PARTICLEHANDLER_H_ */
