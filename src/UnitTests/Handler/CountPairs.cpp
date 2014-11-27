/*
 * CountPairs.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "CountPairs.h"

namespace unitTest {

/**
 * \brief Sets up the handler by setting cnt to 0.
 */
CountPairs::CountPairs() :
		cnt(0) {
}

CountPairs::~CountPairs() {
}

/**
 * \brief This method increments cnt by 1, thereby counting the number of particle pairs.
 * @param p1 First Particle in the counted pair
 * @param p2 Second Particle in the counted pair
 */
void CountPairs::compute(Particle& p1, Particle& p2) {
	cnt++;
}

}
