/*
 * CuboidGenerator.h
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef CUBOIDGENERATOR_H_
#define CUBOIDGENERATOR_H_

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <log4cxx/logger.h>

#include "MaxwellBoltzmannDistribution.h"
#include "utils/Vector.h"
#include "ParticleInput.h"


/**
 * \brief Particle generator for a 3D rectangular grid of particles.
 *
 * The class has to be constructed with a targeted ParticleContainer
 * and input file name.
 */
class CuboidGenerator : public ParticleInput
{
private:
	const char* filename;
	void generateCuboid(std::list<Particle>& particleList,
						utils::Vector<double, 3> corner_position,
						int num_particles[3],
						double distance,
						double mass,
						utils::Vector<double, 3> velocity,
						double brown_factor = 0.1);

public:
	/**
	 * \brief Initialize the CuboidGenerator with a targeted ParticleContainer and an input file.
	 *
	 * @param_particles Targeted ParticleContainer in which the particles will be saved.
	 * @param_filename Input file from which the cuboid definitions are taken.
	 */
	CuboidGenerator(ParticleContainer& param_particles, const char* param_filename)
		: ParticleInput(param_particles), filename(param_filename) {
	}

	virtual ~CuboidGenerator() {
	}

	virtual void input();
};


#endif /* CUBOIDGENERATOR_H_ */
