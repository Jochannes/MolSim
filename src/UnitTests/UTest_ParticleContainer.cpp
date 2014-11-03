/*
 * UTest_ParticleContainer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "UTest_ParticleContainer.h"

#include <list>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( UTest_ParticleContainer );

/**
 * Set up the particle container with 20 particles.
 */
void UTest_ParticleContainer::setUp()
{
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;
    for(int i = 0; i < 20;i++)
    {
		Particle p(x, v, m);
		partContainer.particleList.push_back(p);
    }
}

void UTest_ParticleContainer::tearDown()
{
}

/**
 * \brief Method for testing if ParticleContainer.iterate_all"()" iterates over the correct number of particles.
 */
void UTest_ParticleContainer::testIterateCount(){
	countParticles *cntPart = new countParticles();
	partContainer.iterate_all(*cntPart);
	CPPUNIT_ASSERT(cntPart->cnt == partContainer.particleList.size());
}

/**
 * \brief Method for testing if ParticleContainer.iterate_pairs"()" iterates over the correct number of particle pairs.
 */
void UTest_ParticleContainer::testIteratePairCount(){
	countPairs *cntPairs = new countPairs();
	partContainer.iterate_pairs(*cntPairs);
	CPPUNIT_ASSERT(cntPairs->cnt == partContainer.particleList.size() * (partContainer.particleList.size() - 1));
}
