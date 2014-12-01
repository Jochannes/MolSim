/*
 * UTest_ForceCalculator_LennardJones.h
 *
 *  Created on: Nov 4, 2014
 *      Author: johannes
 */

#ifndef UTEST_FORCECALCULATOR_LENNARDJONES_H_
#define UTEST_FORCECALCULATOR_LENNARDJONES_H_

#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "handler/ForceCalculator_LennardJones.h"

namespace unitTest {

/**
 * \brief Class for testing the force calculator for the Lennard-Jones potential.
 *
 * This class tests if the potential well is set right and attractive and repulsive regions are right.
 */
class UTest_ForceCalculator_LennardJones: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_ForceCalculator_LennardJones );
	CPPUNIT_TEST(testPotentialWell);
	CPPUNIT_TEST(testAttraction);
	CPPUNIT_TEST(testRepulsion);
	CPPUNIT_TEST(testNewton);
	CPPUNIT_TEST_SUITE_END();

private:
	double r_well;							//!< Distance of the potential well
	Particle p1;							//!< First Particle used for force calculations
	Particle p2;							//!< Second Particle used for force calculations
	ForceCalculator_LennardJones fLennard;	//!< ForceCalculator used for force calculation tests

public:
	void setUp();
	void tearDown();
	void testPotentialWell();
	void testAttraction();
	void testRepulsion();
	void testNewton();
};

}

#endif /* UTEST_FORCECALCULATOR_LENNARDJONES_H_ */
