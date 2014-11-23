/*
 * marker_handler.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#include "marker_handler.h"
#include "utils/Vector.h"

namespace unitTest {

marker_handler::marker_handler() {
}

marker_handler::~marker_handler() {
}

/**
 * \brief This method sets the velocity of the particle to 1000, therefore marking it.
 * @param p Particle to mark
 */
void marker_handler::compute(Particle& p) {
	p.getV() = utils::Vector<double, 3>(1000);
}

}
