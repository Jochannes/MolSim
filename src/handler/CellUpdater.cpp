/*
 * CellUpdater.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#include "CellUpdater.h"
#include "ParticleContainer.h"

/**
 * \brief This method updates the ParticleContainer storing the particle.
 *
 * This method checks if the particle should be
 * in a different container and updates the parent
 * container accordingly.
 */
void CellUpdater::compute(Particle& p) {
	if(cellCont->calcCell(p.getX()) != oldContainerIndex){
		cellCont->add(p);
		cellCont->remove(p, oldContainerIndex);
	}
}
