/*
 * PositionCalculator.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef COORDINATECALCULATOR_H_
#define COORDINATECALCULATOR_H_

#include "../ParticleHandler.h"
#include "../Particle.h"
#include "../utils/Vector.h"
#include "../global.h"

/**
 * \brief Class for defining the interface used for position calculation.
 *
 * This class defines the inteface used for position calculation and therefore
 * enables the calculation method to be changed easily.
 */
class PositionCalculator : public ParticleHandler
{
public:
	PositionCalculator();
	virtual ~PositionCalculator();

	virtual void compute(Particle& P);
};


#endif /* COORDINATECALCULATOR_H_ */
