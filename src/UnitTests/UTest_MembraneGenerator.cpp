/*
 * UTest_MembraneGenerator.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "UTest_MembraneGenerator.h"
#include "Handler/CuboidLengthHandler.h"

#include <list>


using namespace std;
using namespace utils;


namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_MembraneGenerator);

/**
 * \brief Set up a ParticleContainer with the MembraneGenerator.
 */
void UTest_MembraneGenerator::setUp() {

	// generate particles
	std::list<Particle> partList;
	MembraneGenerator memGen = MembraneGenerator(corner_position, num_particles, distance, mass, velocity);
	memGen.input(partList);

	//Convert from List to Vector of pointers
	vector<Particle> particleVector;
	for( list<Particle>::iterator it = partList.begin();
		 it != partList.end();
		 it++ )
	{
		particleVector.push_back(*it);
	}

	partContainer = SimpleContainer(particleVector);
}

/**
 * \brief Free the used resources.
 */
void UTest_MembraneGenerator::tearDown() {
}

/**
 * \brief Method for testing if the right number of particles was generated.
 */
void UTest_MembraneGenerator::testCount() {
	CPPUNIT_ASSERT(
			num_particles[0] * num_particles[1]
					== partContainer.size());
}

/**
 * \brief Method for testing if the generated membrane has the right length in all two dimensions.
 */
void UTest_MembraneGenerator::testLength() {

	//Calculate the length
	CuboidLengthHandler calcLength;
	partContainer.iterate_all(calcLength);

	//Test the length in all 2 dimensions
	for (int i = 0; i < 2; i++) {
		CPPUNIT_ASSERT(
				calcLength.length[i] - (num_particles[i] - 1) * distance
						< pow(10, -12));
	}
}

}
