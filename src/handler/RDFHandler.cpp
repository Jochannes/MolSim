/*
 * RDFHandler.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#include "RDFHandler.h"
#include "utils/Vector.h"

using namespace utils;

RDFHandler::RDFHandler(double arg_dr, int arg_intervalCnt) : dr(arg_dr), intervalCnt(arg_intervalCnt) {
	intervals = new int[intervalCnt];
}

RDFHandler::~RDFHandler() {
}

/**
 * \brief Adds this particle pair to the right distance interval.
 * @param p1 First particle for which the distance interval is calculated.
 * @param p2 Second particle for which the distance interval is calculated.
 */
void RDFHandler::compute(Particle& p1, Particle& p2) {
	double distance = (p1.getX() - p2.getX()).L2Norm();
	intervals[(int)(distance / dr)]++;
}

