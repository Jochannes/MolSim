/*
 * cuboidLengthHandler.h
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#ifndef CUBOIDLENGTHHANDLER_H_
#define CUBOIDLENGTHHANDLER_H_

#include "Particle.h"
#include "ParticleHandler.h"

namespace unitTest {

/**
 * \brief Class for calculating the length of the cuboid saved in the ParticleContainer in 3 dimensions.
 */
class cuboidLengthHandler: public ParticleHandler {
private:
	bool initialized[3];
	double lowerBorder[3];
	double upperBorder[3];
public:
	double length[3];

	cuboidLengthHandler();
	virtual ~cuboidLengthHandler();

	virtual void compute(Particle& P);
};

}

#endif /* CUBOIDLENGTHHANDLER_H_ */
