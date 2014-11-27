/*
 * Check_Reflection.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: johannes
 */

#include "Check_Reflection.h"
#include "utils/Vector.h"

namespace unitTest {

Check_Reflection::Check_Reflection() :
		notZero(true), range(0), count(0) {
}

Check_Reflection::~Check_Reflection() {
}

/**
 * \brief This method checks if the force is not equal 0.
 * @param p Particle to check
 */
void Check_Reflection::compute(Particle& p) {
	bool check = false;
	for (int dim = 0; dim < 3; dim++) {
		check |= p.getX()[dim] < range
				|| (boundary[dim] - p.getX()[dim]) < range;
	}
	if (check) {
		notZero &= p.getF().L2Norm() != 0;
		count++;
	}
}

}
