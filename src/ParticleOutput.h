/*
 * ParticleOutput.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEOUTPUT_H_
#define PARTICLEOUTPUT_H_

#include "ParticleContainer.h"

/**
 * \brief Abstract class for defining an interface for the output of particle containers.
 */
class ParticleOutput {
protected:
	/* particle container from which the particles are exported. */
	ParticleContainer& container;

public:
	ParticleOutput(ParticleContainer& param_container) :
			container(param_container) {
	}

	virtual ~ParticleOutput() {
	}

	/** Exports the particle container using respective output method.
	 *
	 */
	virtual void output(int iteration) = 0;

};

#endif /* PARTICLEOUTPUT_H_ */
