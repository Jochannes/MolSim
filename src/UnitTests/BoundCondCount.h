/*
 * BoundCondCount.h
 *
 *  Created on: Nov 26, 2014
 *      Author: johannes
 */

#ifndef BOUNDCONDCOUNT_H_
#define BOUNDCONDCOUNT_H_

#include "BoundaryCondition/BoundaryCondition.h"

namespace unitTest {

/**
 * \brief BoundaryCondition for counting the number of particle containers and particles being called.
*/
class BoundCondCount : public BoundaryCondition {
public:
	BoundCondCount(int side, bool boundCells, bool haloCells) : cnt(0), cntPart(0), BoundaryCondition(side, boundCells, haloCells) { }

	int cnt; //!< Counts the number of calls to the impose method.
	int cntPart; //!< Counts the number of calls to particles.

	void impose(SimpleContainer* cont);
};

}

#endif /* BOUNDCONDCOUNT_H_ */
