/*
 * ForceCalculatorLennardJones.h
 *
 *  Created on: Oct 30, 2014
 *      Author: johannes
 */

#ifndef FORCECALCULATORLENNARDJONES_H_
#define FORCECALCULATORLENNARDJONES_H_

#include "ForceCalculator.h"
#include "../Particle.h"
#include "../utils/Vector.h"
#include "../global.h"

// TODO: Latex installieren und kompilieren!!

/**
 * \brief Class for calculating the force between two particles caused by the Lennard-Jones-potential.
 *
 * This class implements the calculation of the force caused by the Lennard-Jones-potential.
 * This force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{24 \cdot \epsilon}{\left( \left\lVert x_i - x_j \right\rVert_2 \right)^2} \cdot \left( \left( \frac{\sigma}{\left\lVert x_i - x_j \right\rVert_2}^6 - 2 \cdot \left( \frac{\sigma}{\left\lVert x_i - x_j \right\rVert_2} \right)^{12} \right) \cdot \left( x_j - x_i \right)
 * \f]
 */
class ForceCalculator_LennardJones: public ForceCalculator {
public:
	ForceCalculator_LennardJones();
	virtual ~ForceCalculator_LennardJones();

	virtual void compute(Particle& P1, Particle& P2);
};

#endif /* FORCECALCULATORLENNARDJONES_H_ */
