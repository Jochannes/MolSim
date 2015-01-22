/*
 * Check_Force.h
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef CHECK_FORCE_H_
#define CHECK_FORCE_H_

#include "Particle.h"
#include "ParticleHandler.h"
#include "utils/Vector.h"


namespace unitTest {

/**
 * \brief ParticleHandler for testing if particles with a specified type have a specified force.
 */
class Check_Force: public ParticleHandler {
private:
	bool successful;	//!< whether the test was successful
	int type;	//!< type of the particles to test
	utils::Vector<double, 3> force;	//!< the force to test

public:
	Check_Force(int arg_type, utils::Vector<double, 3> arg_force)
		: successful(true), type(arg_type), force(arg_force)
	{ }

	virtual ~Check_Force() {
	}

	virtual void compute(Particle& p);

	bool success() {
		return successful;
	}
};

}

#endif /* CHECK_FORCE_H_ */
