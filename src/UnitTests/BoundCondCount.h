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
	BoundCondCount(int side, bool boundCells, bool haloCells, bool cntCorner) : cnt(0), cntPart(0), cntCorner(cntCorner), BoundaryCondition(side, boundCells, haloCells) { }
	BoundCondCount(CellContainer* cellCont, int side, bool boundCells, bool haloCells, bool cntCorner) : cnt(0), cntPart(0), cntCorner(cntCorner), BoundaryCondition(cellCont, side, boundCells, haloCells) { }

	int cnt; //!< Counts the number of calls to the impose method.
	int cntPart; //!< Counts the number of calls to particles.
	bool cntCorner; //!< Determines if higher-order calls at the edges and corners are counted (for periodic boundary). This requires a pointer to the cell container!

	void impose(SimpleContainer* cont);
};

}

#endif /* BOUNDCONDCOUNT_H_ */
