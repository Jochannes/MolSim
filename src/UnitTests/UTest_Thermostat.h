/*
 * UTest_Thermostat.h
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_THERMOSTAT_H_
#define UTEST_THERMOSTAT_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>


#include "ParticleInput.h"

using namespace std;

namespace unitTest {

/**
 * \brief Class for testing the Thermostat.
 *
 * This TestFixture tests if the Thermostat works correctly.
 *
 */
class UTest_Thermostat: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_Thermostat );
	CPPUNIT_TEST(testTemperatureControl);
	CPPUNIT_TEST_SUITE_END();

private:
	ParticleInput* input;	//!< Method for generating the particles for testing.
	int num_dimensions;		//!< Number of dimensions
	int size; 				//!< number of particles per dimension of the test cuboid.
	double init_temp;		//!< initial temperature.
	double target_temp;		//!< target temperature
	double delta_temp;		//!< temperature difference

public:
	UTest_Thermostat()
		: input(NULL), num_dimensions(3), size(5), init_temp(40.0), target_temp(20.0), delta_temp(-5.0)
	{ }

	void setUp();
	void tearDown();
	void testTemperatureControl();
};

}

#endif /* UTEST_THERMOSTAT_H_ */
