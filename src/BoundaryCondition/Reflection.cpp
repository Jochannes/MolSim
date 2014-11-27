/*
 * Reflection.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#include "Reflection.h"
#include "handler/ReflectionHandler.h"

/**
 * \brief Calls ReflectionHandler for all particles in the container.
 * @param cont Particle container for which the reflection is calculated.
 *
 * ReflectionHandler reflects all particles from
 * the specified side of the container.
 */
void Reflection::impose(SimpleContainer* cont) {
	ReflectionHandler reflect;
	reflect.side = BoundaryCondition::side;
	reflect.boundary = BoundaryCondition::boundary;
	cont->iterate_all(reflect);
}
