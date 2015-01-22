/*
 * ForceCalculator_Constant.h
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_CONSTANT_H_
#define FORCECALCULATOR_CONSTANT_H_


#include "ForceCalculator.h"
#include "Particle.h"
#include "utils/Vector.h"
#include <cfloat>


/**
 * \brief Class for adding a constant force to a subset of particles for a specified period of time.
 *
 */
class ForceCalculator_Constant : public ForceCalculator
{
private:
	utils::Vector<double, 3> force;	//!< the force to add to the particles
	double start_time;	//!< when to start adding the force
	double end_time;	//!< when to stop adding the force
	int type;			//!< type of the particles to change

public:
	ForceCalculator_Constant(utils::Vector<double, 3> arg_force, int arg_type, double arg_start_time = 0.0, double arg_end_time = DBL_MAX);
	virtual ~ForceCalculator_Constant();

	/**
	 * /brief Function for adding the force to a particle.
	 */
	virtual void compute(Particle& p);

	/**
	 * /brief Function for calculating the force between two particles.
	 *
	 * Since this is done per single particle, this method does nothing.
	 */
	virtual void compute(Particle& p1, Particle& p2) {}


	double getStartTime() {
		return start_time;
	}

	double getEndTime() {
		return end_time;
	}
};


#endif /* FORCECALCULATOR_CONSTANT_H_ */
