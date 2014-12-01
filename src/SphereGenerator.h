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
 * \brief Particle generator for a sphere of particles in 3D of 2D grid respectively.
 *
 * The class has to be constructed with all neccessary parameters needed for generating the sphere/circle.
 */
class SphereGenerator: public ParticleInput {
private:

	utils::Vector<double, 3> center_position;	//!< Position of the center.
	int radius;				//!< Number of particles along the radius.
	double distance;		//!< Distance between two particles (lattice constant).
	double mass;			//!< Mass of a single particle.
	utils::Vector<double, 3> velocity;	//!< Main velocity of all particles. The velocity will be superposed by Brownian motion.

	bool use3D;		//!< Specifies wheather a 3D sphere should be generated. If set to false, a 2D circle will be generated.


	/**
	 * \brief Generates a particle in the sphere/circle grid.
	 *
	 * @param particleList List of particles to store the generated particle.
	 * @param x Normalised X coordinate in the grid relative to the center.
	 * @param y Normalised Y coordinate in the grid relative to the center.
	 * @param z Normalised Z coordinate in the grid relative to the center.
	 */
	void genParticle(std::list<Particle>& particleList, int x, int y, int z);

	/**
	 * \brief Generates a row of particles parallel to the Z-axis as part of a sphere in the sphere/circle grid.
	 * It will be generated from the center to 'size' and from center to '-size'.
	 * If size is negative, it will be autmatically calculated so that it fits into the shape of a sphere.
	 *
	 * @param particleList List of particles to store the generated particles.
	 * @param x Normalised X coordinate in the grid relative to the center.
	 * @param y Normalised Y coordinate in the grid relative to the center.
	 * @param size Normalised size of the row from the center to one end.
	 */
	void genRow(std::list<Particle>& particleList, int x, int y, int size=-1);

	/**
	 * \brief Generates a 2D circle in the grid.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	void genCircle(std::list<Particle>& particleList);

	/**
	 * \brief Generates a 3D sphere in the grid.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	void genSphere(std::list<Particle>& particleList);


public:
	/**
	 * \brief Initialize the SphereGenerator with all neccessary parameters needed for generating the sphere/circle.
	 */
	SphereGenerator(utils::Vector<double, 3> param_center_position, int param_radius, double param_distance,
					double param_mass, utils::Vector<double, 3> param_velocity, bool param_use3D = false, double param_brown_factor = 0.1 )
	:
		center_position(param_center_position), radius(param_radius), distance(param_distance),
		mass(param_mass), velocity(param_velocity), use3D(param_use3D)
	{
	}

	virtual ~SphereGenerator() {
	}

	/**
	 * \brief Generate a sphere or circle.
	 *
	 * Generates a sphere or circle of particles in a grid
	 * using the parameters specified in the constructor.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	virtual void input(std::list<Particle>& particleList) {
		if(use3D)
			genSphere(particleList);
		else
			genCircle(particleList);
	}

	/**
	 * /brief Returns a string representing this sphere.
	 */
	virtual std::string toString();
};

#endif /* SPHEREGENERATOR_H_ */
