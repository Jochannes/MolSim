/*
 * BoundaryCondition.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef BOUNDARYCONDITION_H_
#define BOUNDARYCONDITION_H_

//Forward declaration
class SimpleContainer;

/**
 * \brief Abstract class for defining an interface for boundary conditions.
 */
class BoundaryCondition {
public:
	virtual ~BoundaryCondition() {
	}

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

	bool boundCells; //!< Specifies if the boundary condition acts on boundary cells instead of halo cells.

	/**
	 * /brief Abstract function for imposing the boundary conditions on this container.
	 */
	virtual void impose(SimpleContainer* cont) = 0;
};

#endif /* BOUNDARYCONDITION_H_ */
