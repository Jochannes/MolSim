/*
 * handler.h
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#ifndef MARKER_H_
#define MARKER_H_

#include "ParticleHandler.h"

namespace unitTest {

/**
 * \brief ParticleHandler for marking particles.
 *
 * This handler marks particles by setting their velocity to 1000.
 */
class Marker: public ParticleHandler {
public:
	Marker();
	virtual ~Marker();

	virtual void compute(Particle& p);
};
}

#endif /* MARKER_H_ */
