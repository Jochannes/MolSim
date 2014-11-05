/*
 * countParticles.h
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#ifndef COUNTPARTICLES_H_
#define COUNTPARTICLES_H_

#include "Particle.h"
#include "ParticleHandler.h"

namespace unitTest {

/**
 * \brief Class for counting the number of iterated particles for test purposes.
 */
class countParticles: public ParticleHandler {
public:
	int cnt;
	countParticles();
	virtual ~countParticles();

	virtual void compute(Particle& P);
};

}

#endif /* COUNTPARTICLES_H_ */
