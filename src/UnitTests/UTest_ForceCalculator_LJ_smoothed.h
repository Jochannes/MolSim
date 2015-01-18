/*
 * UTest_ForceCalculator_LJ_smoothed.h
 *
 *  Created on: Jan 18, 2015
 *      Author: johannes
 */

#ifndef UTEST_FORCECALCULATOR_LJ_SMOOTHED_H_
#define UTEST_FORCECALCULATOR_LJ_SMOOTHED_H_

#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "handler/ForceCalculator_LJ_smoothed.h"

namespace unitTest {

/**
 * \brief Class for testing the force calculator for the smoothed Lennard-Jones potential.
 *
 * This class tests if the potential well is set right and attractive and repulsive regions are right.
 */
class UTest_ForceCalculator_LJ_smoothed: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( UTest_ForceCalculator_LJ_smoothed );
	CPPUNIT_TEST(testPotentialWell);
	CPPUNIT_TEST(testAttraction);
	CPPUNIT_TEST(testRepulsion);
	CPPUNIT_TEST(testNewton);
	CPPUNIT_TEST_SUITE_END();

private:
	double r_well;								//!< Distance of the potential well
	double cutoff;							//!< Cutoff distance for fLJ_smoothed
	Particle p1;								//!< First Particle used for force calculations
	Particle p2;								//!< Second Particle used for force calculations
	ForceCalculator_LJ_smoothed fLJ_smoothed;		//!< ForceCalculator used for force calculation tests

public:
	UTest_ForceCalculator_LJ_smoothed() :
			r_well(Particle::def_sigma * pow(2.0, 1.0 / 6)),
			fLJ_smoothed(ForceCalculator_LJ_smoothed(3.0, 2.5)),
			cutoff(Particle::def_sigma * 3.0){
	}

	void setUp();
	void tearDown();
	void testPotentialWell();
	void testAttraction();
	void testRepulsion();
	void testNewton();
};

}

#endif /* UTEST_FORCECALCULATOR_LJ_SMOOTHED_H_ */
