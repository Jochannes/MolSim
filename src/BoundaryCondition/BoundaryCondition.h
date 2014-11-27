/*
 * BoundaryCondition.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef BOUNDARYCONDITION_H_
#define BOUNDARYCONDITION_H_

#include "utils/Vector.h"
#include "ParticleContainer/CellContainer.h"

/**
 * \brief Abstract class for defining an interface for boundary conditions.
 */
class BoundaryCondition {
protected:
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

	/**
	 * \brief Main constructor.
	 *
	 * @param cellCont The CellContainer on which this BoundaryCondition is acting.
	 * @param side Side on which this BoundaryCondition is acting.
	 * @param boundCells Specifies if this BoundaryCondition is acting on boundary cells instead of halo cells.
	 *
	 * This method automatically calculates the boundary of the passed cell container.
	 */
	BoundaryCondition(CellContainer* cellCont, int side, bool boundCells) : side(side), boundCells(boundCells)
	{
		boundary[0] = (cellCont->cellCount[0] - 1) * cellCont->cutoff;
		boundary[1] = (cellCont->cellCount[1] - 1) * cellCont->cutoff;
		boundary[2] = (cellCont->cellCount[2] - 1) * cellCont->cutoff;
	}

	/**
	 * \brief Main constructor.
	 * @param side Side on which this BoundaryCondition is acting.
	 * @param boundCells Specifies if this BoundaryCondition is acting on boundary cells instead of halo cells.
	 */
	BoundaryCondition(int side, bool boundCells) : side(side), boundCells(boundCells) {}

public:

	bool boundCells; //!< Specifies if the boundary condition acts on boundary cells instead of halo cells.
	utils::Vector<double, 3> boundary; //!< Boundary of the CellContainer (not equal to domain size!).

	virtual ~BoundaryCondition() {
	}

	/**
	 * /brief Abstract function for imposing the boundary conditions on this container.
	 */
	virtual void impose(SimpleContainer* cont) = 0;
};

#endif /* BOUNDARYCONDITION_H_ */
