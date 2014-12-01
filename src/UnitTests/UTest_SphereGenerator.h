/*
 * UTest_SphereGenerator.h
 *
 *  Created on: Nov 27, 2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_SPHEREGENERATOR_H_
#define UTEST_SPHEREGENERATOR_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SphereGenerator.h"
#include "ParticleContainer/SimpleContainer.h"

#include <list>


namespace unitTest {

/**
 * \brief Class for testing the SphereGenerator.
 *
 * This TestFixture tests if the particle list generated
 * by SphereGenerator has the right number of particles.
 *
 */
class UTest_SphereGenerator: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_SphereGenerator );
	CPPUNIT_TEST(testCount2D);
	CPPUNIT_TEST(testCount3D);
	CPPUNIT_TEST_SUITE_END();

private:
	std::list<Particle> plist2;			//!< Particle list containing the 2D circle for testing
	std::list<Particle> plist3;			//!< Particle list containing the 3D sphere for testing
	double center_position[3];			//!< Position of the center of the sphere
	int    radius;						//!< Number of particles along the radius
	double distance;					//!< Distance between particles
	double mass;						//!< Mass of the particles
	double velocity[3];					//!< Velocity of the particles

public:
	UTest_SphereGenerator() : radius(20), distance(1.1225), mass(1){
	}
	void setUp();
	void tearDown();
	void testCount2D();
	void testCount3D();
};

}

#endif /* UTEST_SPHEREGENERATOR_H_ */
