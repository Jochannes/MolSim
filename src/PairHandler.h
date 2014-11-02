/*
 * PairHandler.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PAIRHANDLER_H_
#define PAIRHANDLER_H_

#include "Particle.h"

/**
 * \brief Abstract class for defining the interface of processing two particles.
 */
class PairHandler
{
public:
	PairHandler() {
	}

	virtual ~PairHandler() {
	}

	virtual void compute(Particle& P1, Particle& P2) = 0;

};


#endif /* PAIRHANDLER_H_ */
