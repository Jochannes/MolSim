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
#include "ParticleContainer.h"
#include "cuboidLengthHandler.h"

using namespace std;

namespace unitTest {

/**
 * \brief Class for testing the CuboidGenerator.
 *
 * This TestFixture tests if the ParticleContainer generated
 * by CuboidGenerator has the right number of particles
 * and the right size in all dimensions.
 *
 */
class UTest_CuboidGenerator: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_CuboidGenerator );
	CPPUNIT_TEST(testCount);
	CPPUNIT_TEST(testLength);CPPUNIT_TEST_SUITE_END()
	;

private:
	ParticleContainer partContainer; //!< Particle container for testing.
	char filename[15] = "cuboidTest.txt";
	double corner_position[3];
	int num_particles[3];
	double distance, mass;
	double velocity[3];

public:
	void setUp();
	void tearDown();
	void testCount();
	void testLength();
};

}

#endif /* UTEST_CUBOIDGENERATOR_H_ */
