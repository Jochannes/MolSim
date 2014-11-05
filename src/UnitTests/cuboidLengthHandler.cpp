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
 */
void cuboidLengthHandler::compute(Particle& P) {
	for (int i = 0; i < 3; i++) {
		if (!initialized) {
			lowerBorder[i] = P.getX()[i];
			upperBorder[i] = P.getX()[i];
			length[i] = 0;
		} else {
			if (lowerBorder[i] > P.getX()[i]) {
				lowerBorder[i] = P.getX()[i];
				length[i] = upperBorder[i] - lowerBorder[i];
			} else if (upperBorder[i] < P.getX()[i]) {
				upperBorder[i] = P.getX()[i];
				length[i] = upperBorder[i] - lowerBorder[i];
			}
		}
	}
}

}
