/*
 * CuboidGenerator.h
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef CUBOIDGENERATOR_H_
#define CUBOIDGENERATOR_H_

#include "ParticleInput.h"

/**
 * \brief Particle generator for a 3D rectangular grid of particles.
 *
 * The class has to be constructed with a targeted ParticleContainer
 * and input file name.
 */
class CuboidGenerator: public ParticleInput {
private:
	const char* filename;

public:
	/**
	 * \brief Initialize the CuboidGenerator with a targeted ParticleContainer and an input file.
	 *
	 * @param param_particles Targeted ParticleContainer in which the particles will be saved.
	 * @param param_filename Input file from which the cuboid definitions are taken.
	 */
	CuboidGenerator(std::list<Particle>& param_particleList,
			const char* param_filename) :
			ParticleInput(param_particleList), filename(param_filename) {
	}

	virtual ~CuboidGenerator() {
	}

	/**
	 * \brief Read input from a file.
	 *
	 * Reads all lines from the file specified in the constructor
	 * and saves them in the ParticleContainer specified in the constructor.
	 */
	virtual void input();
};

#endif /* CUBOIDGENERATOR_H_ */
