/*
 * UTest_CuboidGenerator.h
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#ifndef UTEST_CUBOIDGENERATOR_H_
#define UTEST_CUBOIDGENERATOR_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "CuboidGenerator.h"
#include "ParticleContainer/SimpleContainer.h"
#include "Handler/CuboidLengthHandler.h"

using namespace std;

namespace unitTest {

/**
 * \brief Class for testing the CuboidGenerator.
 *
 * This TestFixture tests if the ParticleContainer generated
 * by CuboidGenerator has the right number of particles
 * and the right size in all dimensions. It does so by
 * creating a test file and then reading it in with the
 * CuboidGenerator.
 *
 */
class UTest_CuboidGenerator: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_CuboidGenerator );
	CPPUNIT_TEST(testCount);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST_SUITE_END();

private:
	SimpleContainer partContainer; 		//!< Particle container for testing.
	double corner_position[3];				//!< Position of the lower left front-side corner of the cuboid
	int num_particles[3];					//!< Number of particles per dimension
	double distance;						//!< Distance between particles
	double mass;							//!< Mass of the particles
	double velocity[3];						//!< Velocity of the particles

public:
	UTest_CuboidGenerator() {
	}
	void setUp();
	void tearDown();
	void testCount();
	void testLength();
};

}

#endif /* UTEST_CUBOIDGENERATOR_H_ */
