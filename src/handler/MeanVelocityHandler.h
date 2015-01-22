/*
 * MeanVelocityHandler.h
 *
 *  Created on: 08.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef MEANVELOCITYHANDLER_H_
#define MEANVELOCITYHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"
#include "utils/Vector.h"


/**
 * \brief Class for calculating the mean velocity along an axis of all particles, which match a specified type.
 */
class MeanVelocityHandler: public ParticleHandler
{
private:
	const int direction;	//!< id of component to use for calculation. x: 0, y: 1, z: 2
	const int type;			//!< type of the particles to iterate. -1 for all.
	double sum;		//!< sum of velocities.
	int count;		//!< amount of particles encountered.

public:
	MeanVelocityHandler(int arg_direction, int arg_type = -1) :
		direction(arg_direction), type(arg_type), sum(0.0), count(0)
	{ }

	virtual ~MeanVelocityHandler() {
	}

	/**
	 * \brief Method for calculating the mean velocity (of one component) for each particle.
	 *
	 * The velocities of each particles are added and stored in 'sum'.
	 * Also 'count' will store the number of particles encountered.
	 *
	 * @param p particle from which the velocity is taken.
	 */
	virtual void compute(Particle& p);


	/**
	 * \brief Returns the mean velocity in one direction.
	 */
	double getMeanV() {
		return (sum / double(count));
	}
};


#endif /* MEANVELOCITYHANDLER_H_ */
