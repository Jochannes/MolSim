/*
 * ForceCalculator_Gravity.h
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_GRAVITY_H_
#define FORCECALCULATOR_GRAVITY_H_


#include "ForceCalculator.h"
#include "../Particle.h"
#include "../utils/Vector.h"
#include "../global.h"


/**
 * \brief Class for calculating the gravitational force between two particles.
 *
 * This class implements the calculation of the gravitational force between two particles.
 * This force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{m_i m_j}{\left( \left\lVert x_i - x_j \right\rVert_2 \right)^3} \cdot \left( x_j - x_i \right)
 * \f]
 */
class ForceCalculator_Gravity : public ForceCalculator
{
public:
	ForceCalculator_Gravity();
	virtual ~ForceCalculator_Gravity();

	virtual void compute(Particle& P1, Particle& P2);
};


#endif /* FORCECALCULATOR_GRAVITY_H_ */
