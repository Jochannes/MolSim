/*
 * PeriodicHandler.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: johannes
 */

#include "PeriodicHandler.h"
#include "utils/Vector.h"
#include "Particle.h"

PeriodicHandler::PeriodicHandler(CellContainer* arg_cells, int arg_side, bool arg_move) : cellCont(arg_cells), side(arg_side), move(arg_move) {
}

PeriodicHandler::~PeriodicHandler() {
}

/**
 * \brief Moves or copies the particle to the other end of the domain.
 * @param p Particle to copy.
 *
 * After setting the x-Position of the particle to the other end of the domain,
 * the particle is updated by adding it to the container with the new coordinates.
 * The cell handler Periodic will then remove the old particle.
 */
void PeriodicHandler::compute(Particle& p) {
	if (move) { //moves the particle, if it is not virtual
		if (!p.getVirtual()) {
			//Choose the right side of the particle container
			if (side % 2 == 0) {
				p.getX()[side / 2] += cellCont->effDomain[side / 2];
			} else {
				p.getX()[side / 2] -= cellCont->effDomain[side / 2];
			}
			cellCont->add(p);
		}
	} else { //copies the particle, sets the new particle as a virtual one.
		double virtV[3] = {0, 0, 0};
		Particle virtP = Particle(p.getX(), virtV, p.getM(), p.getType(), p.getEpsilon(), p.getSigma(), true);
		if (side % 2 == 0) {
			virtP.getX()[side / 2] += cellCont->effDomain[side / 2];
		} else {
			virtP.getX()[side / 2] -= cellCont->effDomain[side / 2];
		}
		cellCont->add(virtP);
	}
}

