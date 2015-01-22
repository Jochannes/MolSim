/*
 * UTest_ForceCalculator_Constant.cpp
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "UTest_ForceCalculator_Constant.h"
#include "CuboidGenerator.h"
#include "Handler/Check_Force.h"

#include <list>


namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ForceCalculator_Constant);

/**
 * \brief Set up a ParticleContainer with the CuboidGenerator.
 */
void UTest_ForceCalculator_Constant::setUp() {
	//Set standard parameters
	corner_position[0] = 0.0;
	corner_position[1] = 0.0;
	corner_position[2] = 0.0;
	num_particles[0] = 5;
	num_particles[1] = 5;
	num_particles[2] = 5;
	distance = 1.0;
	mass = 1.0;
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;

	// generate particles
	std::list<Particle> partList;
	CuboidGenerator cubGen = CuboidGenerator(corner_position, num_particles, distance, mass, velocity, type1);
	cubGen.input(partList);

	//Convert from List to Vector of pointers
	vector<Particle> particleVector;
	for( list<Particle>::iterator it = partList.begin();
		 it != partList.end();
		 it++ )
	{
		particleVector.push_back(*it);
	}

	// mark some particles for change
	for (int i=0; i < particleVector.size(); i++) {
		if( i%3 == 0 ) {
			particleVector[i].setType(type2);
		}
	}

	// create the particle container
	partContainer = SimpleContainer(particleVector);
}

/**
 * \brief Free the used resources.
 */
void UTest_ForceCalculator_Constant::tearDown() {
}


/**
 * \brief Method for testing if the right particles were changed.
 */
void UTest_ForceCalculator_Constant::testForce() {

	// apply the force
	ForceCalculator_Constant fc(force, type2);
	partContainer.iterate_all(fc);

	// check if type1 particles have not changed
	Check_Force check1(type1, 0.0);
	partContainer.iterate_all(check1);
	CPPUNIT_ASSERT( check1.success() );

	// check if type2 particles have the right force
	Check_Force check2(type2, force);
	partContainer.iterate_all(check2);
	CPPUNIT_ASSERT( check2.success() );
}


}

