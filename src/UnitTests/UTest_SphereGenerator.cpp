/*
 * UTest_SphereGenerator.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: Jochannes, DanielCAlbert
 */


#include "UTest_SphereGenerator.h"

#include <list>
#define _USE_MATH_DEFINES
#include <cmath>

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_SphereGenerator);

/**
 * \brief Set up a particle lists with the SphereGenerator.
 *
 */
void UTest_SphereGenerator::setUp() {
	//Set standard parameters
	center_position[0] = 0.0;
	center_position[1] = 0.0;
	center_position[2] = 0.0;
	radius = 20;
	distance = 1.1225;
	mass = 1.0;
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;

	// generate particles
	SphereGenerator sGen2 = SphereGenerator(center_position, radius, distance, mass, velocity, false);
	SphereGenerator sGen3 = SphereGenerator(center_position, radius, distance, mass, velocity, true);

	sGen2.input(plist2);
	sGen3.input(plist3);
}

/**
 * \brief Free the used resources.
 */
void UTest_SphereGenerator::tearDown() {
}

/**
 * \brief Method for testing if the right number of particles was generated in 2D mode.
 */
void UTest_SphereGenerator::testCount2D() {
	int min_size, actual_size, max_size;

	actual_size = plist2.size();
	min_size = (pow(radius-2, 2) * M_PI);
	max_size = (pow(radius, 2) * M_PI);

	CPPUNIT_ASSERT( (actual_size >= min_size)  &&  (actual_size <= max_size) );
}

/**
 * \brief Method for testing if the right number of particles was generated in 3D mode.
 */
void UTest_SphereGenerator::testCount3D() {
	int min_size, actual_size, max_size;

	actual_size = plist3.size();
	min_size = (pow(radius-2, 3) * 4.0/3.0 * M_PI);
	max_size = (pow(radius, 3) * 4.0/3.0 * M_PI);

	CPPUNIT_ASSERT( (actual_size >= min_size)  &&  (actual_size <= max_size) );
}


}
