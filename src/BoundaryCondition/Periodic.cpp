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
 * PeriodicHandler sets the x-Position of the particle to the value at
 * the other end of the domain. The particle is therefore automatically
 * copied in the next cell update.
 */
void Periodic::impose(SimpleContainer* cont) {
	PeriodicHandler periodic(BoundaryCondition::cellCont, BoundaryCondition::side, cont->halo);
	cont->iterate_all(periodic);
}

