/*
 * UTest_ForceCalculator_Gravity.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: johannes
 */

#include "UTest_ForceCalculator_Gravity.h"
#include "handler/VelocityCalculator.h"

// global variable for calculation. See "src/global.h".
extern double delta_t;

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ForceCalculator_Gravity);

void UTest_ForceCalculator_Gravity::setUp() {
	double x[] = { 0, 0, 0 };
	p = Particle(x, vel, m, 1);
	fGrav = ForceCalculator_Gravity(g_grav);
}

/**
 * \brief Free the used resources.
 */
void UTest_ForceCalculator_Gravity::tearDown() {
}

/**
 * \brief Method for testing the force calculated by ForceCalculator_Gravity.
 *
 * It is tested whether the force is independent of position and velocity
 * and linear in weight.
 */
void UTest_ForceCalculator_Gravity::testForce() {

	//Calculate reference force
	fGrav.compute(p);
	utils::Vector<double, 3> force0 = p.getF();

	//Test independence of x and v
	for(int i = 0; i < 100; i++){
		p.getV()[0] = 0;
		p.getV()[1] = 0;
		p.getV()[2] = 0;
		for(int j = 0; j < 100; j++){
			p.getX()[i % 3]++;
			p.getV()[j % 3]++;
			p.getF()[0] = 0;
			p.getF()[1] = 0;
			p.getF()[2] = 0;
			fGrav.compute(p);
			CPPUNIT_ASSERT((p.getF() - force0).L2Norm() < pow(10, -12));
		}
	}

	//Test linear correlation with m
	for(int i = 0; i < 100; i++){
		p = Particle(p.getX(), vel, m * i, 1);
		fGrav.compute(p);
		CPPUNIT_ASSERT((p.getF() - force0 * i).L2Norm() < pow(10, -12));
	}
}

/**
 * \brief Method for testing if the force calculated by ForceCalculator_LennardJones is 0 in the potential well.
 */
void UTest_ForceCalculator_Gravity::testAcceleration() {
	VelocityCalculator velCalc;

	//Test linear correlation with m
	for(int i = 1; i < 100; i++){
		p = Particle(p.getX(), vel, m * i, 1);
		fGrav.compute(p);
		velCalc.compute(p);

		CPPUNIT_ASSERT(p.getV()[1] - 0.5 * delta_t * g_grav < pow(10, -12));
	}
}

} /* namespace unitTest */
