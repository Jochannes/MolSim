/*
 * MembraneGenerator.h
 *
 *  Created on: 22.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef MEMBRANEGENERATOR_H_
#define MEMBRANEGENERATOR_H_

#include "ParticleInput.h"

/**
 * \brief Particle generator for a membrane of particles in a rectangular grid.
 *
 * The class has to be constructed with all necessary parameters needed for generating the membrane.
 * In the moment only 2-dimensional membranes can be generated.
 * A square of four particles can be marked with a different type.
 */
class MembraneGenerator: public ParticleInput {
private:

	utils::Vector<double, 3> corner_position; //!< Position of lower left front-side corner.
	int num_particles[2];	//!< Number of particles in two dimensions.
	double distance;	//!< Distance between two particles (lattice constant).
	double mass;			//!< Mass of a single particle.
	double epsilon; 	//!< Lennard-Jones parameter epsilon for the particles.
	double sigma; 		//!< Lennard-Jones parameter sigma for the particles.
	int type;				//!< Type of the particles.
	utils::Vector<double, 3> velocity;//!< Main velocity of all particles.

	int mark_type;	//!< Type of the marked particles.
	int mark_pos_x; //!< Relative X-coordinate of the lower left corner of the mark.
	int mark_pos_y; //!< Relative Y-coordinate of the lower left corner of the mark.

public:

	/**
	 * \brief Initialize the MembraneGenerator with all neccessary parameters needed for generating the membrane.
	 *
	 */
	MembraneGenerator(utils::Vector<double, 3> param_corner_position,
			int param_num_particles[3], double param_distance,
			double param_mass, utils::Vector<double, 3> param_velocity,
			int param_type = 0, double param_epsilon = 5.0, double param_sigma = 1.0,
			int param_mark_type = 0, int param_mark_pos_x = -1, int param_mark_pos_y = -1 )
		:
			corner_position(param_corner_position), distance(param_distance), mass(param_mass),
			type(param_type), epsilon(param_epsilon), sigma(param_sigma), velocity(param_velocity),
			mark_type(param_mark_type), mark_pos_x(param_mark_pos_x), mark_pos_y(param_mark_pos_y)
	{
		num_particles[0] = param_num_particles[0];
		num_particles[1] = param_num_particles[1];
		num_particles[2] = param_num_particles[2];
	}

	virtual ~MembraneGenerator() {
	}

	/**
	 * \brief Generate a membrane.
	 *
	 * Generates a membrane of particles in a rectangular grid
	 * using the parameters specified in the constructor.
	 *
	 * @param particleList List of particles to store the generated particles.
	 */
	virtual void input(std::list<Particle>& particleList);

	/**
	 * /brief Returns a string representing this membrane.
	 */
	virtual std::string toString();


	int getSizeX() {
		return num_particles[0];
	}

	int getSizeY() {
		return num_particles[1];
	}
};

#endif /* MEMBRANEGENERATOR_H_ */
