/*
 * countParticles.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "countParticles.h"

namespace unitTest {

/**
 * \brief Sets up the handler by setting cnt to 0.
 */
countParticles::countParticles() :
		cnt(0) {
}

countParticles::~countParticles() {
}

/**
 * \brief This method increments cnt by 1, thereby counting the number of particle.
* @param p Particle to count
 */
void countParticles::compute(Particle& p) {
	cnt++;
}

}
