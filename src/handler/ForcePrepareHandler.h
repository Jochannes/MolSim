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
#include "utils/Vector.h"
#include "global.h"



/**
 * \brief Class for resetting the calculated forces for a new iteration step.
 *
 */
class ForcePrepareHandler : public ParticleHandler
{
public:
	ForcePrepareHandler();
	virtual ~ForcePrepareHandler();

	virtual void compute(Particle& p);
};

#endif /* FORCEPREPAREHANDLER_H_ */
