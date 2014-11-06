/*
 * cuboidLengthHandler.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#include "cuboidLengthHandler.h"

namespace unitTest {

cuboidLengthHandler::cuboidLengthHandler() {
}

cuboidLengthHandler::~cuboidLengthHandler() {
}

/**
 * \brief This method checks if the particle defines a new border and sets the cuboid length accordingly.
* @param p Particle to check
 */
void cuboidLengthHandler::compute(Particle& p) {

	//per dimension
	for (int i = 0; i < 3; i++) {

		//have the borders been initialized?
		if (!initialized) {
			lowerBorder[i] = p.getX()[i];
			upperBorder[i] = p.getX()[i];
			length[i] = 0;
		} else {

			//set new borders if particles is outside of the old borders.
			if (lowerBorder[i] > p.getX()[i]) {
				lowerBorder[i] = p.getX()[i];
				length[i] = upperBorder[i] - lowerBorder[i];
			} else if (upperBorder[i] < p.getX()[i]) {
				upperBorder[i] = p.getX()[i];
				length[i] = upperBorder[i] - lowerBorder[i];
			}
		}
	}
}

}
