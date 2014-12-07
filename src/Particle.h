/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "utils/Vector.h"

/**
 * \brief Class for saving all the parameters associated with a particle.
 *
 * This class saves the position, velocity, current and recent force
 * and provides functions for accessing these parameters. It furthermore
 * overrides the operator for comparing particles.
 */
class Particle {

private:

	/** the position of the particle */
	utils::Vector<double, 3> x;

	/** the velocity of the particle */
	utils::Vector<double, 3> v;

	/** the force effective on this particle */
	utils::Vector<double, 3> f;

	/** the force which was effective on this particle */
	utils::Vector<double, 3> old_f;

	/** the mass of this particle */
	double m;

	double epsilon; //!< Lennard-Jones parameter epsilon for this particle.
	double sigma; //!< Lennard-Jones parameter sigma for this particle.

	/** type of the particle.
	 * -1: virtual particle (e.g. for boundary conditions)
	 * >=0: real particle
	 */
	int type;

public:
	static double def_sigma;	//!< Default sigma value used for the Lennard-Jones potential
	static double def_epsilon;	//!< Default epsilon value used for the Lennard-Jones potential

	Particle(int type = 0);

	Particle(const Particle& other);

	Particle(
			// for visualization, we need always 3 coordinates
			// -> in case of 2d, we use only the first and the second
			utils::Vector<double, 3> x_arg, utils::Vector<double, 3> v_arg,
			double m_arg, int type = 0, double epsilon_arg = def_epsilon, double sigma_arg = def_sigma);

	Particle(utils::Vector<double, 3> x_arg, utils::Vector<double, 3> v_arg,
			 utils::Vector<double, 3> f_arg, utils::Vector<double, 3> old_f_arg,
			 double m_arg, double epsilon_arg = def_epsilon, double sigma_arg = def_sigma, int type_arg = 0);

	virtual ~Particle();

	utils::Vector<double, 3>& getX();

	utils::Vector<double, 3>& getF();

	utils::Vector<double, 3>& getOldF();

	utils::Vector<double, 3>& getV();

	double getM();

	double getEpsilon();
	double getSigma();

	int getType();

	bool operator==(Particle& other);

	std::string toString();
};

std::ostream& operator<<(std::ostream& stream, Particle& p);

#endif /* PARTICLE_H_ */
