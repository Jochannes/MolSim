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
 * \brief BoundaryCondition for counting the number of particle containers being called.
*/
class BoundCondCount : public BoundaryCondition {
public:
	BoundCondCount(int side, bool boundCells) : cnt(0), BoundaryCondition(side, boundCells) {}

	int cnt; //!< Counts the number of calls to the impose method.

	void impose(SimpleContainer* cont);
};

}

#endif /* BOUNDCONDCOUNT_H_ */
