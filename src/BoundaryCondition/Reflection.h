/*
 * Reflection.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef REFLECTION_H_
#define REFLECTION_H_

#include "BoundaryCondition.h"
#include "ParticleContainer/SimpleContainer.h"

/**
 * \brief BoundaryCondition for reflecting particles on the domain border.
 *
 * This BoundaryCondition reflects all
 * particles from the domain border.
 */
class Reflection: public BoundaryCondition {
public:
	Reflection(int side) : side(side), boundCells(true) {}

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

	bool boundCells; //!< Set to true; this boundary condition acts on boundary cells.

	void impose(SimpleContainer* cont);
};

#endif /* REFLECTION_H_ */
