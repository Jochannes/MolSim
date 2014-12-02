/*
 * ReflectionHandler.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#include "ReflectionHandler.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "utils/Vector.h"
#include "Particle.h"

ReflectionHandler::ReflectionHandler() {
}

ReflectionHandler::~ReflectionHandler() {
}

/**
 * \brief Reflects the particle by a counter particle, if close enough to the side.
 * @param p Particle to reflect
 *
 * This method reflects the particle from the specified
 * side of the container by introducing a counter particle
 * at its border, if the particle is close enough to the border
 * (i.e. in the repulsive zone of the Lennard-Jones potential).
 */
void ReflectionHandler::compute(Particle& p) {

	//calculate border of repulsive force
	double limit = pow(2,1/6.0) * p.getSigma();


	//Choose the right side of the particle container for reflection
	if(side % 2 == 0){
		if(p.getX()[side/2] < limit){

			//create counter particle
			Particle counter(p);
			counter.getX()[side/2] = 0;

			//do the reflection
			ForceCalculator_LennardJones reflectionForce;
			reflectionForce.compute(p, counter);
		}
	} else {
		if(boundary[side/2] - p.getX()[side/2] < limit){

			//create counter particle
			Particle counter(p);
			counter.getX()[side/2] = boundary[side/2];

			//do the reflection
			ForceCalculator_LennardJones reflectionForce;
			reflectionForce.compute(p, counter);
		}
	}
}
