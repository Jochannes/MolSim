/*
 * SphereGenerator.h
 *
 *  Created on: 25.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef SPHEREGENERATOR_H_
#define SPHEREGENERATOR_H_

#include "ParticleInput.h"

/**
 * \brief Particle generator for a sphere of particles in 3D grid.
 *
 * The class has to be constructed with all neccessary parameters needed for generating the sphere.
 */
class SphereGenerator: public ParticleInput {
private:

	utils::Vector<double, 3> center_position;	//!< Position of the center.
	int radius;				//!< Number of particles along the radius.
	double distance;		//!< Distance between two particles (lattice constant).
	double mass;			//!< Mass of a single particle.
	utils::Vector<double, 3> velocity;	//!< Main velocity of all particles. The velocity will be superposed by Brownian motion.
	double brown_factor;	//!< Mean velocity of the Brownian motion.

public:
	/**
	 * \brief Initialize the SphereGenerator with all neccessary parameters needed for generating the sphere.
	 */
	SphereGenerator(utils::Vector<double, 3> param_center_position, int param_radius, double param_distance,
					double param_mass, utils::Vector<double, 3> param_velocity, double param_brown_factor = 0.1 )
	:
		center_position(param_center_position), radius(param_radius), distance(param_distance),
		mass(param_mass), velocity(param_velocity), brown_factor(param_brown_factor)
	{
	}

	virtual ~SphereGenerator() {
	}

	/**
	 * \brief Generate a sphere.
	 *
	 * Generates a sphere of particles in a 3D grid
	 * using the parameters specified in the constructor.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	virtual void input(std::list<Particle>& particleList);

	/**
	 * /brief Returns a string representing this sphere.
	 */
	virtual std::string toString();
};

#endif /* SPHEREGENERATOR_H_ */
