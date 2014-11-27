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
 * The class has to be constructed with all neccessary parameters needed for generating the cuboid.
 */
class CuboidGenerator: public ParticleInput {
private:

	utils::Vector<double, 3> corner_position;	//!< Position of lower left front-side corner.
	int num_particles[3];	//!< Number of particles in all three dimensions.
	double distance;		//!< Distance between two particles (lattice constant).
	double mass;			//!< Mass of a single particle.
	utils::Vector<double, 3> velocity;	//!< Main velocity of all particles. The velocity will be superposed by Brownian motion.
	double brown_factor;	//!< Mean velocity of the Brownian motion.

public:
	/**
	 * \brief Initialize the CuboidGenerator with all neccessary parameters needed for generating the cuboid.
	 *
	 */
	CuboidGenerator(utils::Vector<double, 3> param_corner_position, int param_num_particles[3], double param_distance,
					double param_mass, utils::Vector<double, 3> param_velocity, double param_brown_factor = 0.1 )
	:
		corner_position(param_corner_position), distance(param_distance),
		mass(param_mass), velocity(param_velocity), brown_factor(param_brown_factor)
	{
		num_particles[0] = param_num_particles[0];
		num_particles[1] = param_num_particles[1];
		num_particles[2] = param_num_particles[2];
	}

	virtual ~CuboidGenerator() {
	}

	/**
	 * \brief Generate a cuboid.
	 *
	 * Generates a cuboid of particles in a 3D rectangular grid
	 * using the parameters specified in the constructor.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	virtual void input(std::list<Particle>& particleList);

	/**
	 * /brief Returns a string representing this cuboid.
	 */
	virtual std::string toString();
};

#endif /* CUBOIDGENERATOR_H_ */
