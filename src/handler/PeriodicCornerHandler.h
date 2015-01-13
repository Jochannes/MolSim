/*
 * PeriodicCornerHandler.h
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#ifndef PERIODICCORNERHANDLER_H_
#define PERIODICCORNERHANDLER_H_

#include "ParticleHandler.h"
#include "ParticleContainer/CellContainer.h"

/**
 * \brief Handler for creating virtual particles at edges and corners.
 *
 * This handler copies realizes the second and third order copy of
 * particles at edges and corners.
 */
class PeriodicCornerHandler: public ParticleHandler {
public:
	PeriodicCornerHandler(CellContainer* arg_cells, int arg_sides[3]);
	virtual ~PeriodicCornerHandler();

	/**
	 * \brief Integer array defining the sides of the corner/edge on which this condition is imposed.
	 *
	 * The sides are defined as following:
	 * 0: x=0
	 * 1: x=max
	 * 2: y=0
	 * 3: y=max
	 * 4: z=0
	 * 5: z=max
	 * -1: none (for defining edges)
	 */
	int sides[3];

	CellContainer* cellCont; //!< Cell container for adding the virtual particle.

	virtual void compute(Particle& p);
};

#endif /* PERIODICCORNERHANDLER_H_ */
