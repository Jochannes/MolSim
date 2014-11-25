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
	double limit = pow(2,1/6) * ForceCalculator_LennardJones::sigma;

	//Choose the right side of the particle container for reflection
	if(side % 2){
		if(p.getX()[side/2] - cont->contStart[side/2] < limit){

			//create counter particle
			utils::Vector<double, 3> xCounter = p.getX();
			xCounter[side/2] = cont->contStart[side/2];
			double vCounter[] = { 0, 0, 0 };
			Particle counter(xCounter, vCounter, p.getM());

			//do the reflection
			ForceCalculator_LennardJones reflectionForce;
			reflectionForce.compute(p, counter);
		}
	} else {
		if(cont->contEnd[side/2] - p.getX()[side/2] < limit){

			//create counter particle
			utils::Vector<double, 3> xCounter = p.getX();
			xCounter[side/2] = cont->contEnd[side/2];
			double vCounter[] = { 0, 0, 0 };
			Particle counter(xCounter, vCounter, p.getM());

			//do the reflection
			ForceCalculator_LennardJones reflectionForce;
			reflectionForce.compute(p, counter);
		}
	}
}
