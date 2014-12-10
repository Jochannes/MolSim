/*
 * UTest_ParticleFile.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "UTest_ParticleFile.h"
#include "Particle.h"
#include "ParticleContainer/SimpleContainer.h"
#include "ParticleFileReader.h"
#include "ResultOutput.h"

#include <ctime>
#include <cstdlib>

using namespace std;


namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ParticleFile);

/**
 * \brief Auxilliary function for calculating a random double between 0 and 100
 */
static double r()
{
	return (double(rand()) / double(RAND_MAX) * 100.0);
}

/**
 * \brief Set up the unit test: create the particles.
 */
void UTest_ParticleFile::setUp() {
	for(int i = 0; i < 3; i++) {
		// initialize random number generator
		srand(time(NULL));
		srand(rand());

		double x[3] = { r(), r(), r() };
		double v[3] = { r(), r(), r() };
		double f[3] = { r(), r(), r() };
		double old_f[3] = { r(), r(), r() };
		double m = r();
		double epsilon = r();
		double sigma = r();
		int type = i;

		Particle p = Particle(x, v, f, old_f, m, epsilon, sigma, type);
		pList.push_back(p);
	}
}

/**
 * \brief Free the used resources.
 */
void UTest_ParticleFile::tearDown() {
}

/**
 * \brief Performs the IO test.
 */
void UTest_ParticleFile::testIO() {

	// write to file
	SimpleContainer container(pList);
	ResultOutput ro(container, filename);
	ro.output();

	// read from file
	list<Particle> pList2;
	ParticleFileReader fr(filename);
	fr.input(pList2);

	// check
	CPPUNIT_ASSERT(pList.size() == pList2.size());

	for( vector<Particle>::iterator it1 = pList.begin(); it1 != pList.end(); it1++) {
		bool found_equal_particle = false;

		for( list<Particle>::iterator it2 = pList2.begin(); it2 != pList2.end(); it2++) {
			if(*it1 == *it2) {
				found_equal_particle = true;
			}
		}
		CPPUNIT_ASSERT(found_equal_particle);
	}
}


}
