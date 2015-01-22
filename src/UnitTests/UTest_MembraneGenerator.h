/*
 * UTest_MembraneGenerator.h
 *
 *  Created on: 30.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_MEMBRANEGENERATOR_H_
#define UTEST_MEMBRANEGENERATOR_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>


#include "MembraneGenerator.h"
#include "ParticleContainer/SimpleContainer.h"


namespace unitTest {

/**
 * \brief Class for testing the MembraneGenerator.
 *
 */
class UTest_MembraneGenerator: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_MembraneGenerator );
	CPPUNIT_TEST(testCount);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST_SUITE_END();

private:
	SimpleContainer partContainer; 		//!< Particle container for testing.
	utils::Vector<double, 3> corner_position; //!< Position of lower left front-side corner.
	int num_particles[2];	//!< Number of particles in two dimensions.
	double distance;		//!< Distance between two particles (lattice constant).
	double mass;			//!< Mass of a single particle.
	utils::Vector<double, 3> velocity;//!< Main velocity of all particles.

public:
	UTest_MembraneGenerator()
		: distance(1.1225), mass(1)
	{
		corner_position[0] = corner_position[1] = corner_position[2] = 0;
		velocity[0] = velocity[1] = velocity[2] = 0;
		num_particles[0] = num_particles[1] = 5;
	}

	void setUp();
	void tearDown();
	void testCount();
	void testLength();
};

}

#endif /* UTEST_MEMBRANEGENERATOR_H_ */
