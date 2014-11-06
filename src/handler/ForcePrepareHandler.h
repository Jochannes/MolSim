/*
 * ForcePrepareHandler.h
 *
 *  Created on: Nov 2, 2014
 *      Author: johannes
 */

#ifndef FORCEPREPAREHANDLER_H_
#define FORCEPREPAREHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"


/**
 * \brief Class for resetting the calculated forces for a new iteration step.
 *
 */
class ForcePrepareHandler : public ParticleHandler
{
public:
	ForcePrepareHandler();
	virtual ~ForcePrepareHandler();

	/**
	 * \brief This method saves the force calculated for the particle
	 *        in the previous step to OldF and resets the force to 0.
	 * @P particle to prepare
	 */
	virtual void compute(Particle& p);
};

#endif /* FORCEPREPAREHANDLER_H_ */
