/*
 * PositionCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef COORDINATECALCULATOR_H_
#define COORDINATECALCULATOR_H_

#include "ParticleHandler.h"

/**
 * \brief Class for defining the interface used for position calculation.
 *
 * This class defines the inteface used for position calculation and therefore
 * enables the calculation method to be changed easily.
 */
class PositionCalculator: public ParticleHandler {
	int *omit_types;	//!< array of types of particles for which the position update is omitted.
	int omit_count;		//!< size of the array

public:
	PositionCalculator();
	PositionCalculator(int arg_omit_count, int* arg_omit_types);

	virtual ~PositionCalculator();

	/**
	 * \brief Standard method for calculating the particle position.
	 * @param p particle for which a new position is calculated.
	 */
	virtual void compute(Particle& p);
};

#endif /* COORDINATECALCULATOR_H_ */
