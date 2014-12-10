/*
 * Periodic.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: johannes
 */

#include "Periodic.h"

/**
 * \brief Calls PeriodicHandler for all particles in the container.
 * @param cont Particle container from which the particles are copied.
 *
 * For halo cells, PeriodicHandler sets the x-Position of the particle
 * to the value at the other end of the domain and newly adds it to
 * the container. Afterwards, all particles are removed from the cell.
 *
 * For boundary cells, PeriodicHandler copies the particles to the halo
 * cells at the other end of the container by setting the x-Position
 * accordingly. The copied particles are set as being virtual (virt = true).
 */
void Periodic::impose(SimpleContainer* cont) {
	PeriodicHandler periodic(BoundaryCondition::cellCont, BoundaryCondition::side, cont->halo);
	cont->iterate_all(periodic);

	/* Remove all particles. Real particles were copied and virtual
	 * particles will be updated during the iteration over boundary
	 * cells, which comes after the iteration over halo cells.
	 */
	if(cont->halo){
		cont->remove_all();
	}
}
