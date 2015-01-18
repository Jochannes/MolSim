/*
 * UTest_ForceCalculator_LJ_smoothed.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: johannes
 */

#include "UTest_ForceCalculator_LJ_smoothed.h"

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ForceCalculator_LJ_smoothed);

void UTest_ForceCalculator_LJ_smoothed::setUp() {
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;
	p1 = Particle(x, v, m, 1);
	p2 = Particle(x, v, m, 2);
}

/**
 * \brief Free the used resources.
 */
void UTest_ForceCalculator_LJ_smoothed::tearDown() {
}

/**
 * \brief Method for testing if the force calculated by UTest_ForceCalculator_LJ_smoothed is 0 in the potential well.
 */
void UTest_ForceCalculator_LJ_smoothed::testPotentialWell() {

	//Test potential well for x-coordinate
	p2.getX()[0] = r_well;
	fLJ_smoothed.compute(p1, p2);
	CPPUNIT_ASSERT(p1.getF().L2Norm() < pow(10, -12));

	//Test potential well for y-coordinate
	p2.getX()[0] = 0;
	p2.getX()[1] = r_well;
	fLJ_smoothed.compute(p1, p2);
	CPPUNIT_ASSERT(p1.getF().L2Norm() < pow(10, -12));

	//Test potential well for z-coordinate
	p2.getX()[1] = 0;
	p2.getX()[2] = r_well;
	fLJ_smoothed.compute(p1, p2);
	CPPUNIT_ASSERT(p1.getF().L2Norm() < pow(10, -12));
}

/**
 * \brief Method for testing if the force is attractive at farther distances than the potential well.
 */
void UTest_ForceCalculator_LJ_smoothed::testAttraction() {

	//Test the force for 19 distances farther than the potential well
	for (int i = 1; i < 20; i++) {
		p1.getF() = 0.0;
		p2.getF() = 0.0;
		p2.getX()[0] = r_well * (1 + i * 0.1);
		fLJ_smoothed.compute(p1, p2);
		CPPUNIT_ASSERT(p2.getX()[0] > cutoff || p1.getF()[0] > 0);
	}
}

/**
 * \brief Method for testing if the force is repulsive at distances closer than the potential well.
 */
void UTest_ForceCalculator_LJ_smoothed::testRepulsion() {

	//Test the force for 19 distances closer than the potential well
	for (int i = 1; i < 20; i++) {
		p1.getF() = 0.0;
		p2.getF() = 0.0;
		p2.getX()[0] = r_well * (1 - i * 0.05);
		fLJ_smoothed.compute(p1, p2);
		CPPUNIT_ASSERT(p1.getF()[0] < 0);
	}
}

/**
 * \brief Method for testing if the force is equal for both particles (Newton's third law).
 */
void UTest_ForceCalculator_LJ_smoothed::testNewton() {

	//Test the force for 29 distances, both closer and farther than the potential well
	for (int i = 1; i < 30; i++) {
		p1.getF() = 0.0;
		p2.getF() = 0.0;
		p2.getX()[0] = r_well * (i * 0.1);
		fLJ_smoothed.compute(p1, p2);
		CPPUNIT_ASSERT((p1.getF() + p2.getF()).L2Norm() == 0);
	}
}

}
