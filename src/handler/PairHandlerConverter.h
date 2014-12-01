/*
 * PairHandlerConverter.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef PAIRHANDLERCONVERTER_H_
#define PAIRHANDLERCONVERTER_H_

#include "ParticleHandler.h"
#include "PairHandler.h"

/**
 * \brief Handler for converting a PairHandler into a ParticleHandler.
 *
 * This class converts a PairHandler into a ParticleHandler.
 * This functionality is used for iterating over particles
 * from different cells in the linked-cell algorithm.
 */
class PairHandlerConverter: public ParticleHandler {
private:
	PairHandler *original;		//!< Original PairHandler function.
	Particle *partner1;	//!< First particle in the PairHandler::compute() function.

public:
	PairHandlerConverter(PairHandler *original);
	PairHandlerConverter(PairHandler *original, Particle *partner1);
	~PairHandlerConverter();

	void setPartner(Particle *partner1);

	void compute(Particle& p);
};

#endif /* PAIRHANDLERCONVERTER_H_ */
