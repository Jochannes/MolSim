/*
 * Reflection.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef REFLECTION_H_
#define REFLECTION_H_

#include "BoundaryCondition/BoundaryCondition.h"

/**
 * \brief BoundaryCondition for reflecting particles on the domain border.
 *
 * This BoundaryCondition reflects all particles from
 * the domain border. It acts on boundary cells.
 */
class Reflection: public BoundaryCondition {

public:

	Reflection(CellContainer* cont, int side) : BoundaryCondition(cont, side, true, false) {}

	void impose(SimpleContainer* cont);
};

#endif /* REFLECTION_H_ */
