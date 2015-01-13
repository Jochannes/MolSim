/*
 * VarHandler.h
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#ifndef VARHANDLER_H_
#define VARHANDLER_H_

#include "ParticleHandler.h"
/**
 * \brief Handler for calculating the movement variance of the particles.
 */
class VarHandler: public ParticleHandler {
public:
	double varN; //!< Sum of the variances of all particles.

	VarHandler();
	virtual ~VarHandler();

	virtual void compute(Particle& p);
};

#endif /* VARHANDLER_H_ */
