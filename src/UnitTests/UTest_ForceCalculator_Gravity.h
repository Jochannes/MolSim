/*
 * UTest_ForceCalculator_Gravity.h
 *
 *  Created on: Dec 2, 2014
 *      Author: johannes
 */

#ifndef UTEST_FORCECALCULATOR_GRAVITY_H_
#define UTEST_FORCECALCULATOR_GRAVITY_H_

#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "handler/ForceCalculator_Gravity.h"

namespace unitTest {


/**
 * \brief Class for testing the gravity calculation.
 *
 * This class tests if the proportionalities of the gravity to mass, position and velocity are right.
 */
class UTest_ForceCalculator_Gravity : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( UTest_ForceCalculator_Gravity );
	CPPUNIT_TEST(testForce);
	CPPUNIT_TEST(testAcceleration);
	CPPUNIT_TEST_SUITE_END();

private:
	Particle p;				//!< Particle used for force calculations
	double m;				//!< Particle mass
	double vel[3];				//!< Particle velocity
	ForceCalculator_Gravity fGrav;//!< ForceCalculator used for force calculation tests
	double g_grav;				//!< Gravitational acceleration

public:
	UTest_ForceCalculator_Gravity() : g_grav(-10), m(1.0), fGrav(ForceCalculator_Gravity(g_grav)) {
		vel[0] = 0;
		vel[1] = 0;
		vel[2] = 0;
	}

	void setUp();
	void tearDown();
	void testForce();
	void testAcceleration();
};

} /* namespace unitTest */

#endif /* UTEST_FORCECALCULATOR_GRAVITY_H_ */
