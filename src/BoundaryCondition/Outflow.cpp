/*
 * Outflow.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#include "Outflow.h"

/**
 * \brief Removes all particles from this cell.
 * @param cont Particle container to empty.
 *
 * This method should be called for all halo
 * cells when the according boundary condition
 * is set.
 */
void Outflow::impose(SimpleContainer* cont) {
	cont->remove_all();
}
