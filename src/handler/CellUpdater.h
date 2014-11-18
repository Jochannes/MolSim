/*
 * PositionCalculator_Cell.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef CELLUPDATER_H_
#define CELLUPDATER_H_

#include "ParticleHandler.h"
#include "CellContainer.h"

/**
 * \brief Handler for updating the ParticleContainer for all particles.
 */
class CellUpdater: public ParticleHandler {
private:
	CellContainer* cellCont; //!< CellContainer for all particles.

public:
	int oldContainerIndex; //!< Index of the old container storing the particle.

	CellUpdater(CellContainer* cellCont) :
			cellCont(cellCont) {
		oldContainerIndex = 0;
	}

	CellUpdater(int oldContainerIndex, CellContainer* cellCont) :
			oldContainerIndex(oldContainerIndex), cellCont(cellCont) {
	}

	void compute(Particle& p);
};

#endif /* CELLUPDATER_H_ */
