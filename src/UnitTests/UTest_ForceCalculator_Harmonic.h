/*
 * UTest_ForceCalculator_Harmonic.h
 *
 *  Created on: 07.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_FORCECALCULATOR_HARMONIC_H_
#define UTEST_FORCECALCULATOR_HARMONIC_H_


#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "handler/ForceCalculator_Harmonic.h"


namespace unitTest {


/**
 * \brief Class for testing the harmonic potential.
 */
class UTest_ForceCalculator_Harmonic : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( UTest_ForceCalculator_Harmonic );
	CPPUNIT_TEST(testForce);
	CPPUNIT_TEST_SUITE_END();

private:
	ForceCalculator_Harmonic fHarm;	//!< ForceCalculator for force calculation tests
	Particle p[3];					//!< Particles used for tests

	const double k;	//!< stiffness factor
	const double r;	//!< average bond length of the molecule pairs

public:
	UTest_ForceCalculator_Harmonic()
		: k(300), r(1.0), fHarm(300.0, 1.0) {
	}

	void setUp();
	void tearDown();
	void testForce();
};

} /* namespace unitTest */

#endif /* UTEST_FORCECALCULATOR_HARMONIC_H_ */
