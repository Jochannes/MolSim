/*
 * VarHandler.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#include "VarHandler.h"
#include "utils/Vector.h"

using namespace utils;

// global variable for calculation. See "src/global.h".
extern double delta_t;

VarHandler::VarHandler() {
	varN = 0;
}

VarHandler::~VarHandler() {
}

/**
 * \brief Sums up the distances travelled by the particles.
 * @param p particle for which the travelled distance is calculated and added.
 *
 * Altogether, this function realizes the equation:
 * \f[
 * \mbox{VarN}(t) = \sum_{i=1}^N \left| x_i (t) - x_i (t_0) \right|_2^2
 * \f]
 *
 * The next position is calculated using the
 * standard equation used in PositionCalculator.
 * More flexibility could be achieved by passing
 * a PositionCalculator to this handler.
 */
void VarHandler::compute(Particle& p) {
	double a = 0.5 * delta_t * delta_t / p.getM();

	Vector<double, 3> nextPos = p.getX() + delta_t * p.getV() + a * p.getF();
	varN += (nextPos - p.getX()).L2Norm2();
}
