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

void ForcePrepareHandler::compute(Particle& p) {
	p.getOldF() = p.getF();
	p.getF() = 0.0;
}
