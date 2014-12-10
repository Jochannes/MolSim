/*
 * CountParticles.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "CountParticles.h"

namespace unitTest {

/**
 * \brief Sets up the handler by setting cnt to 0.
 */
CountParticles::CountParticles(bool arg_onlyReal) :
		cnt(0), onlyReal(arg_onlyReal) {
}

CountParticles::~CountParticles() {
}

/**
 * \brief This method increments cnt by 1, thereby counting the number of particle.
 * @param p Particle to count
 */
void CountParticles::compute(Particle& p) {
	if (!onlyReal || !p.getVirtual()) {
		cnt++;
	}
}

}
