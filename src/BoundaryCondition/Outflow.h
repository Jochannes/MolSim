/*
 * Outflow.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef OUTFLOW_H_
#define OUTFLOW_H_

#include "BoundaryCondition/BoundaryCondition.h"

/**
 * \brief BoundaryCondition for deleting particles when leaving the domain.
 *
 * This BoundaryCondition removes all particles from the cell.
 * It acts on halo cells, therefore realizing outflow conditions.
 *
 * This is the standard boundary condition the CellContainer.
 */
class Outflow : public BoundaryCondition {

public:

	Outflow(int side) : BoundaryCondition(side, false) {}

	void impose(SimpleContainer* cont);
};

#endif /* OUTFLOW_H_ */
