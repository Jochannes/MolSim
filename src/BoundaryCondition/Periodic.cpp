/*
 * Periodic.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: johannes
 */

#include "Periodic.h"
#include "handler/PeriodicHandler.h"
#include "handler/PeriodicCornerHandler.h"
#include <typeinfo>

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
	PeriodicHandler periodic(BoundaryCondition::cellCont,
			BoundaryCondition::side, cont->halo);
	cont->iterate_all(periodic);

	//treat higher-order copies at corners and edges
	if (!cont->halo) {
		int sides[3];
		sides[0] = BoundaryCondition::side;

		//check x
		if (cont->pos[0] == 1
				&& typeid(*BoundaryCondition::cellCont->boundConds[0])
						== typeid(Periodic)) {
			sides[0] = 0;
		} else if (cont->pos[0] == BoundaryCondition::cellCont->cellCount[0] - 2
				&& typeid(*BoundaryCondition::cellCont->boundConds[1])
						== typeid(Periodic)) {
			sides[0] = 1;
		} else {
			sides[0] = -1;
		}

		//check y
		if (cont->pos[1] == 1
				&& typeid(*BoundaryCondition::cellCont->boundConds[2])
						== typeid(Periodic)) {
			sides[1] = 2;
		} else if (cont->pos[1] == BoundaryCondition::cellCont->cellCount[1] - 2
				&& typeid(*BoundaryCondition::cellCont->boundConds[3])
						== typeid(Periodic)) {
			sides[1] = 3;
		} else {
			sides[1] = -1;
		}

		//check z
		if (cont->pos[2] == 1
				&& typeid(*BoundaryCondition::cellCont->boundConds[4])
						== typeid(Periodic)) {
			sides[2] = 4;
		} else if (cont->pos[2] == BoundaryCondition::cellCont->cellCount[2] - 2
				&& typeid(*BoundaryCondition::cellCont->boundConds[5])
						== typeid(Periodic)) {
			sides[2] = 5;
		} else {
			sides[2] = -1;
		}

		/* Impose special boundary condition:
		 * - Make sure it is only imposed once (by a boundary condition acting on x or y (for y-z-edges)
		 * - Make sure it is only imposed at edges and corners
		 */
		if ((sides[0] != -1 && (sides[1] != -1 || sides[2] != -1) && BoundaryCondition::side < 2) // x-y and x-z-edges, corners
				|| (sides[0] == -1 && sides[1] != -1 && sides[2] != -1 && BoundaryCondition::side < 4)) { // y-z-edges
			PeriodicCornerHandler corner(BoundaryCondition::cellCont, sides);
			cont->iterate_all(corner);
		}
	}

	/* Remove all particles. Real particles were copied and virtual
	 * particles will be updated during the iteration over boundary
	 * cells, which comes after the iteration over halo cells.
	 */
	if (cont->halo) {
		cont->remove_all();
	}
}
