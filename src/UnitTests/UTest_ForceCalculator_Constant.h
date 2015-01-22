/*
 * UTest_ForceCalculator_Constant.h
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_FORCECALCULATOR_CONSTANT_H_
#define UTEST_FORCECALCULATOR_CONSTANT_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>


#include "ParticleContainer/SimpleContainer.h"
#include "handler/ForceCalculator_Constant.h"
#include "utils/Vector.h"


using namespace std;


namespace unitTest {

/**
 * \brief Class for testing ForceCalculator_Constant.
 *
 * This TestFixture creates a ParticleContainer with particles of
 * different types. It uses ForceCalculator_Constant to apply a
 * force to the particles of one type. Afterwards it is checked
 * whether these particles have the right forces and whether the
 * other particles were not changed.
 *
 */
class UTest_ForceCalculator_Constant: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_ForceCalculator_Constant );
	CPPUNIT_TEST(testForce);
	CPPUNIT_TEST_SUITE_END();

private:
	utils::Vector<double, 3> force;		//!< the force to apply to the particles.
	int type1;							//!< type of the particles which are not changed.
	int type2;							//!< type of the particles which are changed.

	SimpleContainer partContainer; 		//!< Particle container for testing.
	double corner_position[3];			//!< Position of the lower left front-side corner of the cuboid
	int num_particles[3];				//!< Number of particles per dimension
	double distance;					//!< Distance between particles
	double mass;						//!< Mass of the particles
	double velocity[3];					//!< Velocity of the particles


public:
	UTest_ForceCalculator_Constant() : force(1.0), distance(1.1225), mass(1), type1(0), type2(1) {
	}
	void setUp();
	void tearDown();
	void testForce();
};

}

#endif /* UTEST_FORCECALCULATOR_CONSTANT_H_ */
