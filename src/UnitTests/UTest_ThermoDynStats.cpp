/*
 * UTest_ThermoDynStats.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: johannes
 */

#include "UTest_ThermoDynStats.h"
#include "CuboidGenerator.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "ParticleInput.h"
#include "utils/Vector.h"

using namespace utils;

extern double delta_t;

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ThermoDynStats);

/**
 * \brief Set up the unit tests.
 */
void UTest_ThermoDynStats::setUp() {

	double x[3] = {0.0, 0.0, 0.0};
	int    n[3] = {5, 5, 5};
	double m    = 1.0;
	double v[3] = {vel, 0.0, 0.0};

	::delta_t = 0.001;

	//Initialize particle list
	ParticleInput* input = new CuboidGenerator(x, n, dist, m, v);
	list<Particle> particleList;
	input->input(particleList);

	//Convert from List to Vector of pointers
	vector<Particle> particleVector;
	for( list<Particle>::iterator it = particleList.begin();
		 it != particleList.end();
		 it++ )
	{
		particleVector.push_back(*it);
	}

	//Initialize particle container
	particles = new SimpleContainer(particleVector);
}

/**
 * \brief Free the used resources.
 */
void UTest_ThermoDynStats::tearDown() {
	std::remove(varFile.c_str());
	std::remove(rdfFile.c_str());
}

/**
 * \brief Tests the thermodynamic statistics calculation in a simple scenario.
 *
 * Since the velocity and all positions are constant, the expected
 * travelled distance and number of neighbours at a certain distance
 * can be estimated easily.
 */
void UTest_ThermoDynStats::testAnalyze() {
	double expVar = pow(::delta_t * vel, 2);

	for(int i = 0; i < avgOver; i++){

		stats->analyze(particles, i);

		//Test if the variance is right
		CPPUNIT_ASSERT(stats->var[i] - expVar < pow(10, -12));

		//Test if all next neighbours are at the distance dist and all second next neighbours at sqrt(2) * dist.
		for(int j = 0; j < ceil(maxrad / dr); j++){
			if((int) (dist / dr) == j ||
					(int) (dist * sqrt(2) / dr) == j){
				CPPUNIT_ASSERT(stats->rdf[i][j] > 0);
			} else {
				CPPUNIT_ASSERT(stats->rdf[i][j] == 0);
			}
		}
	}
}

} /* namespace UnitTest */
