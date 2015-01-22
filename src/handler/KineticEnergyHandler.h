/*
 * KineticEnergyHandler.h
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef KINETICENERGYHANDLER_H_
#define KINETICENERGYHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"
#include "utils/Vector.h"


/**
 * \brief Class for calculating the kinetic energy of all particles in a ParticleContainer.
 * Optionally the mean velocity of the object the particles belong to can be specified.
 * This velocity will be subtracted from the velocity of each particle during calculation.
 */
class KineticEnergyHandler: public ParticleHandler
{
private:
	double E_kin;	//!< Saves the sum of the kinetic energies of all particles.
	utils::Vector<double, 3> v_mean;	//!< mean velocity of the object the particle belongs to.
	int type;		//!< Type of the particles to calculate the kinetic energy. -1 for all.

public:
	KineticEnergyHandler(int param_type = -1) :
		E_kin(0.0), v_mean(0.0), type(param_type)
	{ }

	KineticEnergyHandler(utils::Vector<double, 3> arg_v_mean, int param_type = -1)
		: E_kin(0.0), v_mean(arg_v_mean), type(param_type)
	{ }

	virtual ~KineticEnergyHandler() {
	}

	/**
	 * \brief Method for calculating the kinetic energy for each particle.
	 *
	 * The kinetic energy is calculated for each particle.
	 * The sum is stored in 'E_kin'.
	 *
	 * @param p particle for which the kinetic energy is calculated.
	 */
	virtual void compute(Particle& p);


	/**
	 * \brief Returns the sum of the kinetic energies of all particles.
	 */
	double getKineticEnergy() {
		return E_kin;
	}
};


#endif /* KINETICENERGYHANDLER_H_ */
