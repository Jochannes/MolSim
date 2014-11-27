/*
 * Check_Reflection.h
 *
 *  Created on: Nov 27, 2014
 *      Author: johannes
 */

#ifndef CHECK_REFLECTION_H_
#define CHECK_REFLECTION_H_

#include "ParticleHandler.h"
#include "utils/Vector.h"

namespace unitTest {

/**
 * \brief ParticleHandler for checking if the new force is not equal 0.
 */
class Check_Reflection: public ParticleHandler {
private:
	utils::Vector<double, 3> boundary; //!< Boundary of the CellContainer.
	double range; //!< Range of the force acting from the boundary.

public:
	bool notZero;	//!< All forces unequal 0.

	int count;	//!< How many particles were supposed to be reflected.

	Check_Reflection();

	Check_Reflection(double range, utils::Vector<double, 3> boundary) :
			count(0), notZero(true), range(range), boundary(boundary) {
	}

	~Check_Reflection();

	void compute(Particle& p);
};

}

#endif /* CHECK_REFLECTION_H_ */
