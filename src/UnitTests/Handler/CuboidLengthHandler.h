/*
 * CuboidLengthHandler.h
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
 * \brief ParticleHandler for calculating the length of the cuboid saved in the ParticleContainer in 3 dimensions.
 */
class CuboidLengthHandler: public ParticleHandler {
private:
	bool initialized[3];	//!< saves if the borders have been set
	double lowerBorder[3];	//!< lower value for the cuboid border in each dimension
	double upperBorder[3];	//!< upper value for the cuboid border in each dimension
public:
	double length[3];		//!< Calculated overall length per dimension

	CuboidLengthHandler();
	virtual ~CuboidLengthHandler();

	virtual void compute(Particle& p);
};

}

#endif /* CUBOIDLENGTHHANDLER_H_ */
