/*
 * ParticleInput.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEINPUT_H_
#define PARTICLEINPUT_H_

#include "ParticleContainer.h"


/**
 * \brief Abstract class for defining an interface for the input of particle lists.
 */
class ParticleInput
{
protected:
	ParticleContainer& container;

public:
	ParticleInput(ParticleContainer& param_container)
		: container(param_container) {
	}

	virtual ~ParticleInput() {
	}

	/** Fills the ParticleContainer with respective input.
	 *
	 */
	virtual void input() = 0;

};


#endif /* PARTICLEINPUT_H_ */
