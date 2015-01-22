/*
 * ForceCalculator_Harmonic.h
 *
 *  Created on: 22.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef FORCECALCULATOR_HARMONIC_H_
#define FORCECALCULATOR_HARMONIC_H_


#include "ForceCalculator.h"
#include "Particle.h"

namespace unitTest {
	class UTest_ForceCalculator_Harmonic;
}

/**
 * \brief Class for adding interaction between neighboring particles using the harmonic potential.
 *
 * Note: You have to specify the surrounding particles of each particle using Particle::setNeighbor().
 */
class ForceCalculator_Harmonic : public ForceCalculator
{
	friend class unitTest::UTest_ForceCalculator_Harmonic;


private:
	double k;	//!< stiffness constant
	double r;	//!< average bond length of a molecule pair

	/**
	 * /brief Auxiliary function for adding the (harmonic) interaction between direct neighbors.
	 */
	void calc_direct(Particle& p1, Particle& p2);

	/**
	 * /brief Auxiliary function for adding the (harmonic) interaction between diagonal neighbors.
	 */
	void calc_diag(Particle& p1, Particle& p2);

public:
	ForceCalculator_Harmonic(double arg_k = 300.0, double arg_r = 1.0);
	virtual ~ForceCalculator_Harmonic();

	/**
	 * /brief Function for adding the (harmonic) interaction with its neighbors to a particle.
	 */
	virtual void compute(Particle& p);

	/**
	 * /brief Function for calculating the force between two particles.
	 *
	 * Since this is calculated per single particle, this method does nothing.
	 */
	virtual void compute(Particle& p1, Particle& p2) {}
};


#endif /* FORCECALCULATOR_HARMONIC_H_ */
