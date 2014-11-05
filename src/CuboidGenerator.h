/*
 * CuboidGenerator.h
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef CUBOIDGENERATOR_H_
#define CUBOIDGENERATOR_H_

#include "ParticleInput.h"


class CuboidGenerator : public ParticleInput
{
private:
	const char* filename;

public:
	CuboidGenerator(ParticleContainer& param_particles, const char* param_filename)
		: ParticleInput(param_particles), filename(param_filename) {
	}

	virtual ~CuboidGenerator() {
	}

	virtual void input();
};


#endif /* CUBOIDGENERATOR_H_ */
