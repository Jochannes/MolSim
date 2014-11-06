/*
 * countPairs.h
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#ifndef COUNTPAIRS_H_
#define COUNTPAIRS_H_

#include "Particle.h"
#include "PairHandler.h"

namespace unitTest {

/**
 * \brief Class for counting the number of iterated particle pairs for test purposes.
 */
class countPairs: public PairHandler {
public:
	int cnt;	//!< Number of counted particle pairs
	countPairs();
	virtual ~countPairs();

	virtual void compute(Particle& p1, Particle& p2);
};

}
#endif /* COUNTPAIRS_H_ */
