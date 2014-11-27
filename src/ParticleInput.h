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
 * \brief Abstract class for defining an interface for the input of particle lists.
 */
class ParticleInput {
public:
	ParticleInput() {
	}

	virtual ~ParticleInput() {
	}

	/** Fills a particle list using respective input method.
	 *
	 * @param particleList List of particles to store the particles.
	 */
	virtual void input(std::list<Particle>& particleList) = 0;

	/**
	 * /brief Returns a string representing this object.
	 */
	virtual std::string toString() = 0;
};

#endif /* PARTICLEINPUT_H_ */
