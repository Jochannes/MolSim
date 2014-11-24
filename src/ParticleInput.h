/*
 * ParticleInput.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEINPUT_H_
#define PARTICLEINPUT_H_


#include "Particle.h"

#include <list>

/**
 * \brief Abstract class for defining an interface for the input of particle containers.
 */
class ParticleInput {
protected:
	/* particle container to which the particles are read. */
	std::list<Particle>& particleList;

public:
	ParticleInput(std::list<Particle>& param_particleList) :
			particleList(param_particleList) {
	}

	virtual ~ParticleInput() {
	}

	/** Fills the particle container with respective input.
	 *
	 */
	virtual void input() = 0;

};

#endif /* PARTICLEINPUT_H_ */
