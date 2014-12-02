/*
 * CountParticles.h
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#ifndef COUNTPARTICLES_H_
#define COUNTPARTICLES_H_

#include "ParticleHandler.h"

namespace unitTest {

/**
 * \brief ParticleHandler for counting the number of iterated particles for test purposes.
 */
class CountParticles: public ParticleHandler {
public:
	int cnt;		//!< Number of counted particles.
	bool onlyReal; 	//!< If set, this handler only counts no virtual particles.
	CountParticles(bool arg_onlyReal = false);
	virtual ~CountParticles();

	virtual void compute(Particle& p);
};

}

#endif /* COUNTPARTICLES_H_ */
