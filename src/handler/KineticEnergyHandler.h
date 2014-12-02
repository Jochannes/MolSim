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

/**
 * \brief Class for calculating the kinetic energy of all particles in a ParticleContainer.
 *
 */
class KineticEnergyHandler: public ParticleHandler
{
private:
	double E_kin;	//!< Saves the sum of the kinetic energies of all particles.

public:
	KineticEnergyHandler() :
		E_kin(0.0)
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
