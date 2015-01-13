/*
 * RDFHandler.h
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#ifndef RDFHANDLER_H_
#define RDFHANDLER_H_

#include "PairHandler.h"

/**
 * \brief Handler for calculating the radial pair distribution function.
 *
 * The radial pair distribution function is calculated by
 * counting the number of particles in different distance
 * intervals. This is done using by this handler.
 */
class RDFHandler: public PairHandler {
private:
	double dr;			//!< Radius discretization length for the radial pair distribution function.
	int intervalCnt;	//!< Number of intervals in the radial pair distribution function.

public:
	int* intervals; //!< Number of particles in each distance interval.

	RDFHandler(double arg_dr, int arg_intervalCnt);
	virtual ~RDFHandler();

	virtual void compute(Particle& p1, Particle& p2);
};

#endif /* RDFHANDLER_H_ */
