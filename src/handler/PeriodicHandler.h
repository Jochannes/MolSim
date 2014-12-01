/*
 * PeriodicHandler.h
 *
 *  Created on: Dec 1, 2014
 *      Author: johannes
 */

#ifndef PERIODICHANDLER_H_
#define PERIODICHANDLER_H_

#include "ParticleHandler.h"
#include "ParticleContainer/CellContainer.h"

/**
 * \brief Handler for moving particles to the other side of the domain.
 *
 * By moving or copying particles from the halo/boundary cells on one end to the boundary/halo
 * cells on the other end of the domain, this handler realizes periodic boundary conditions.
 */
class PeriodicHandler: public ParticleHandler {
public:
	PeriodicHandler(CellContainer* arg_cells, int arg_side, bool arg_move);
	virtual ~PeriodicHandler();

	/**
	 * \brief Integer defining the domain side on which this condition is imposed.
	 *
	 * The domain sides are defined as following:
	 * 0: x=0
	 * 1: x=max
	 * 2: y=0
	 * 3: y=max
	 * 4: z=0
	 * 5: z=max
	 */
	int side;

	bool move; //!< Specifies if the particle is moved ore copied.
	CellContainer* cellCont; //!< Cell container for adding the virtual particle.

	utils::Vector<double, 3> boundary; //!< Boundary of the CellContainer.

	virtual void compute(Particle& p);
};

#endif /* PERIODICHANDLER_H_ */
