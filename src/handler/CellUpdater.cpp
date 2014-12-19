/*
 * CellUpdater.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#include "CellUpdater.h"
#include "ParticleContainer/SimpleContainer.h"

/**
 * \brief This method updates the SimpleContainer storing the particle.
 *
 * This method checks if the particle should be
 * in a different container and updates the parent
 * container accordingly.
 */
void CellUpdater::compute(Particle& p) {
	if(cellCont->getCell(p.getX()) != oldContainer){
		cellCont->add(p);
		toRemove.push_back(pair<Particle, SimpleContainer*>(p, oldContainer));
	}
}
