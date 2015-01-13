/*
 * Periodic.h
 *
 *  Created on: Dec 1, 2014
 *      Author: johannes
 */

#ifndef PERIODIC_H_
#define PERIODIC_H_

#include "BoundaryCondition.h"

/**
 * \brief Periodic BoundaryCondition, moving particles from one end of the domain to the other.
 *
 * This BoundaryCondition moves all particles from the halo cells of one side
 * to the boundary cells of the other side and copies the particles from the boundary
 * cells on one side into the halo cells of the other.
 * The parameter BoundaryCondition::side specifies the side the particles are copied from.
 * This BoundaryCondition acts on halo cells and boundary cells.
 */
class Periodic: public BoundaryCondition {
public:

	Periodic(CellContainer* cont, int side) : BoundaryCondition(cont, side, true, true) {}

	void impose(SimpleContainer* cont);
};

#endif /* PERIODIC_H_ */
