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
 * \brief Abstract class for defining the interface of processing a single particle.
 */
class ParticleHandler
{
public:
	ParticleHandler() {
	}

	virtual ~ParticleHandler() {
	}

	virtual void compute(Particle& P) = 0;

};


#endif /* PARTICLEHANDLER_H_ */
