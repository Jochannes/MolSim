/*
 * UTest_ParticleContainer.h
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#ifndef UTEST_PARTICLECONTAINER_H_
#define UTEST_PARTICLECONTAINER_H_

#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ParticleContainer/SimpleContainer.h"

/**
 * \brief Namespace for all UnitTests and associated auxiliary classes.
 */
namespace unitTest {

/**
 * \brief Class for testing the particle container.
 *
 * This class tests if the iterate methods iterate over the right number of particles and particle pairs.
 */
class UTest_SimpleContainer : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( UTest_SimpleContainer );
	CPPUNIT_TEST(testSize);
	CPPUNIT_TEST(testAddSize);
	CPPUNIT_TEST(testIterateAll);
	CPPUNIT_TEST(testIterateCount);
	CPPUNIT_TEST(testIteratePairCount);
	CPPUNIT_TEST(testIteratePairHalfCount);
	CPPUNIT_TEST_SUITE_END();

private:
	int numParticles = 20; 				//!< Number of particles with which the container will be initialized.
	SimpleContainer partContainer; 	//!< ParticleContainer for testing.

public:
	void setUp();
	void tearDown();
	void testSize();
	void testAddSize();
	void testIterateAll();
	void testIterateCount();
	void testIteratePairCount();
	void testIteratePairHalfCount();
};

}

#endif /* UTEST_PARTICLECONTAINER_H_ */
