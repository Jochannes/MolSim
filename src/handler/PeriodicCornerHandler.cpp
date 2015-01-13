/*
 * PeriodicCornerHandler.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#include "PeriodicCornerHandler.h"
#include "utils/Vector.h"
#include "Particle.h"

PeriodicCornerHandler::PeriodicCornerHandler(CellContainer* arg_cells, int arg_sides[3]) : cellCont(arg_cells) {
	sides[0] = arg_sides[0];
	sides[1] = arg_sides[1];
	sides[2] = arg_sides[2];
}

PeriodicCornerHandler::~PeriodicCornerHandler() {
}

/**
 * \brief Copies the particle to the opposite edge or corner of the domain.
 * @param p Particle to copy.
 */
void PeriodicCornerHandler::compute(Particle& p) {

	//copy the particle to the opposite edge or corner of the domain.
	double virtV[3] = { 0, 0, 0 };
	Particle virtP = Particle(p.getX(), virtV, p.getM(), p.getType(),
			p.getEpsilon(), p.getSigma(), true);
	for (int i = 0; i < 3; i++) {
		if (sides[i] != -1) {
			if (sides[i] % 2 == 0) {
				virtP.getX()[sides[i] / 2] += cellCont->effDomain[sides[i] / 2];
			} else {
				virtP.getX()[sides[i] / 2] -= cellCont->effDomain[sides[i] / 2];
			}
		}
	}
	cellCont->add(virtP);

	//make additional copies to the three opposite edges if this is a corner
	if(sides[0] != -1 && sides[1] != -1 && sides[2] != -1){
		for(int i = 0; i < 3; i++){
			virtP = Particle(p.getX(), virtV, p.getM(), p.getType(),
					p.getEpsilon(), p.getSigma(), true);
			if (sides[i] % 2 == 0) {
				virtP.getX()[sides[i] / 2] += cellCont->effDomain[sides[i] / 2];
			} else {
				virtP.getX()[sides[i] / 2] -= cellCont->effDomain[sides[i] / 2];
			}
			if (sides[(i+1)%3] % 2 == 0) {
				virtP.getX()[sides[(i+1)%3] / 2] += cellCont->effDomain[sides[(i+1)%3] / 2];
			} else {
				virtP.getX()[sides[(i+1)%3] / 2] -= cellCont->effDomain[sides[(i+1)%3] / 2];
			}
			cellCont->add(virtP);
		}
	}
}

