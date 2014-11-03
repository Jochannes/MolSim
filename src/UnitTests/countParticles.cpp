/*
 * countParticles.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "countParticles.h"

countParticles::countParticles() {
	cnt = 0;
}

countParticles::~countParticles() {
}

/**
 * \brief This method increments cnt by 1.
 */
void countParticles::compute(Particle& P)
{
	cnt++;
}
