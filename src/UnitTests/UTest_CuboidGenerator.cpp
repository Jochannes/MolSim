/*
 * UTest_CuboidGenerator.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#include "UTest_CuboidGenerator.h"

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_CuboidGenerator);

/**
 * \brief Set up a ParticleContainer with the CuboidGenerator.
 *
 * During setup a test file is created and then read in by the CuboidGenerator.
 * The particles are saved in the ParticleContainer partContainer.
 * The properties of these particles are then checked.
 */
void UTest_CuboidGenerator::setUp() {
	//Set standard parameters
	corner_position[0] = 0.0;
	corner_position[1] = 0.0;
	corner_position[2] = 0.0;
	num_particles[0] = 40;
	num_particles[1] = 8;
	num_particles[2] = 2;
	distance = 1.1225;
	mass = 1.0;
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;

	//Write file for testing.
	ofstream myfile;
	myfile.open(filename);
	myfile << "1\n";
	myfile << corner_position[0] << " " << corner_position[1] << " "
			<< corner_position[2] << " ";
	myfile << num_particles[0] << " " << num_particles[1] << " "
			<< num_particles[2] << " ";
	myfile << distance << " ";
	myfile << mass << " ";
	myfile << velocity[0] << " " << velocity[1] << " " << velocity[2] << endl;
	myfile.close();

	//read in file using a CuboidGenerator
	CuboidGenerator cubGen = CuboidGenerator(partContainer, filename);
	cubGen.input();
}

void UTest_CuboidGenerator::tearDown() {
	remove(filename);
}

/**
 * \brief Method for testing if the right number of particles was generated.
 */
void UTest_CuboidGenerator::testCount() {
	CPPUNIT_ASSERT(
			num_particles[0] * num_particles[1] * num_particles[2]
					== partContainer.size());
}

/**
 * \brief Method for testing if the generated cuboid has the right length in all three dimensions.
 */
void UTest_CuboidGenerator::testLength() {
	cuboidLengthHandler calcLength;
	partContainer.iterate_all(calcLength);
	for (int i = 0; i < 3; i++) {
		CPPUNIT_ASSERT(
				calcLength.length[i] - (num_particles[i] - 1) * distance
						< pow(10, -12));
	}
}

}
