/*
 * BoundCondCount.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: johannes
 */

#include "BoundCondCount.h"

/**
 * \brief Counts the number of particle containers this method is called for.
 * @param cont Particle container to count.
 */
void BoundCondCount::impose(SimpleContainer* cont) {
	cnt++;
}
