/*
 * ForceCalculator_Gravity.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ForceCalculator_Gravity.h"

#include <cmath>


ForceCalculator_Gravity::ForceCalculator_Gravity() {
}


ForceCalculator_Gravity::~ForceCalculator_Gravity() {
}


/**
 * \brief Function for computing the gravitational force between two particles.
 *
 * Calculates the gravitational force between two particles
 * and adds it to the force acting on the first particle.
 * The force is calculated using the following equation:
 * \f[
 * F_{ij} = \frac{m_i m_j}{\left( \left\lVert x_i - x_j \right\rVert_2 \right)^3} \cdot \left( x_j - x_i \right)
 * \f]
 */
void ForceCalculator_Gravity::compute(Particle& P1, Particle& P2)
{
	double distance = (P2.getX() - P1.getX()).L2Norm();

	utils::Vector<double, 3> force = P1.getM() * P2.getM() / pow(distance, 3) * (P2.getX() - P1.getX());

	P1.getF() = P1.getF() + force;
	//P2.getF() = P1.getF() - force;		// according to Newton's third law: F_P1 = -F_P2, use alternative iteration method
}

