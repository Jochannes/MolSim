/*
 * Marker.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#include "Marker.h"
#include "utils/Vector.h"

namespace unitTest {

Marker::Marker() {
}

Marker::~Marker() {
}

/**
 * \brief This method sets the velocity of the particle to 1000, therefore marking it.
 * @param p Particle to mark
 */
void Marker::compute(Particle& p) {
	p.getV() = utils::Vector<double, 3>(1000);
}

}
