/*
 * ForceCalculator_Gravity.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Gravity.h"
#include "utils/Vector.h"

#include <cmath>


ForceCalculator_Gravity::ForceCalculator_Gravity() {
}


ForceCalculator_Gravity::~ForceCalculator_Gravity() {
}


/**
 * \brief Function for computing the gravitational force between two particles.
 *
 * @param p1 First interacting particle (at \f$ x_i \f$ )
 * @param p2 Second interacting particle (at \f$ x_j \f$ )
 *
 * Calculates the gravitational force between two particles
 * and adds it to the force acting on the first particle.
 * The force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{m_i m_j}{\left( \left\| x_i - x_j \right\|_2 \right)^3} \cdot \left( x_j - x_i \right)
 * \f]
 */
void ForceCalculator_Gravity::compute(Particle& p1, Particle& p2)
{
	double distance = (p2.getX() - p1.getX()).L2Norm();

	utils::Vector<double, 3> force = p1.getM() * p2.getM() / pow(distance, 3) * (p2.getX() - p1.getX());

	p1.getF() = p1.getF() + force;
	p2.getF() = p2.getF() - force;		// according to Newton's third law: F_P1 = -F_P2
}

