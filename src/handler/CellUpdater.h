/*
 * PositionCalculator_Cell.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef CELLUPDATER_H_
#define CELLUPDATER_H_

#include "ParticleHandler.h"
#include "ParticleContainer/CellContainer.h"

/**
 * \brief Handler for updating the ParticleContainer for all particles.
 */
class CellUpdater: public ParticleHandler {
private:
	CellContainer* cellCont; //!< CellContainer for all particles.

public:
	SimpleContainer* oldContainer; //!< Pointer to the old container storing the particle.

	/**
	 * \brief List of all outdated particles to remove.
	 *
	 * The first value contains the particle and the second
	 * the container from which to remove it from.
	 */
	list<pair<Particle, SimpleContainer*> > toRemove;

	CellUpdater(CellContainer* cellCont) :
			cellCont(cellCont) {
	}

	CellUpdater(SimpleContainer* oldContainer, CellContainer* cellCont) :
		oldContainer(oldContainer), cellCont(cellCont) {
	}

	void compute(Particle& p);
};

#endif /* CELLUPDATER_H_ */
