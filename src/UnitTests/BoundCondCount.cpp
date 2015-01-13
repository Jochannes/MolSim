/*
 * BoundCondCount.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: johannes
 */

#include "BoundCondCount.h"

namespace unitTest {

/**
 * \brief Counts the number of particle containers this method is called for.
 * @param cont Particle container to count.
 */
void BoundCondCount::impose(SimpleContainer* cont) {
	cnt++;
	cntPart += cont->size();

	//Consider higher-order calls at edges and corners of boundary cells
	if(cntCorner && !cont->halo){
		bool xedge = false;
		int mult = 0;

		//check x
		if (cont->pos[0] == 1 || cont->pos[0] == BoundaryCondition::cellCont->cellCount[0] - 2) {
			xedge = true;
			mult++;
		}

		//check y
		if (cont->pos[1] == 1 || cont->pos[1] == BoundaryCondition::cellCont->cellCount[1] - 2) {
			mult++;
		}

		//check z
		if (cont->pos[2] == 1 || cont->pos[2] == BoundaryCondition::cellCont->cellCount[2] - 2) {
			mult++;
		}

		if(mult == 2 && (BoundaryCondition::side < 2 || (BoundaryCondition::side < 4 && !xedge))){
			cntPart += cont->size();
		}
		if(mult == 3 && BoundaryCondition::side < 2){
			cntPart += 4 * cont->size();
		}
	}
}

}
