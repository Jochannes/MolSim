/*
 * ForcePrepareHandler.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: johannes
 */

#include "ForcePrepareHandler.h"

ForcePrepareHandler::ForcePrepareHandler() {
}

ForcePrepareHandler::~ForcePrepareHandler() {
}


/**
 * \brief This method saves the force calculated for the particle
 * in the previous step to OldF and resets the force to 0.
 */
void ForcePrepareHandler::compute(Particle& p) {
	p.getOldF() = p.getF();
	p.getF()    = 0.0;
}
