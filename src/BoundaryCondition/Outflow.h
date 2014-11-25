/*
 * Outflow.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef OUTFLOW_H_
#define OUTFLOW_H_

#include "BoundaryCondition/BoundaryCondition.h"
#include "ParticleContainer/SimpleContainer.h"

/**
 * \brief BoundaryCondition for deleting particles when leaving the domain.
 *
 * This BoundaryCondition removes all particles from the cell.
 * It should be called for all halo cells,
 * therefore realizing outflow conditions.
 *
 * This is the standard boundary condition the CellContainer.
 */
class Outflow : public BoundaryCondition {
public:
	Outflow(int side) : side(side), boundCells(false) {}

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

	bool boundCells; //!< Set to false; this boundary condition acts on halo cells.

	void impose(SimpleContainer* cont);
};

#endif /* OUTFLOW_H_ */
