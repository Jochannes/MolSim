/*
 * UTest_ParticleContainer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "UTest_ParticleContainer.h"

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( UTest_ParticleContainer );

/**
 * Set up a particle container with 20 particles.
 */
void UTest_ParticleContainer::setUp()
{
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;
	std::list<Particle> initialParticleList;
    for(int i = 0; i < 20;i++)
    {
		Particle p(x, v, m);
		initialParticleList.push_back(p);
    }
    partContainer = ParticleContainer(initialParticleList);
}

void UTest_ParticleContainer::tearDown()
{
}

/**
 * \brief Method for testing if ParticleContainer::iterate_all iterates over the correct number of particles.
 */
void UTest_ParticleContainer::testIterateCount(){
	countParticles cntPart = countParticles();
	partContainer.iterate_all(cntPart);
	CPPUNIT_ASSERT(cntPart.cnt == partContainer.size());
}

/**
 * \brief Method for testing if ParticleContainer::iterate_pairs iterates over the correct number of particle pairs.
 */
void UTest_ParticleContainer::testIteratePairCount(){
	countPairs cntPairs = countPairs();
	partContainer.iterate_pairs(cntPairs);
	CPPUNIT_ASSERT(cntPairs.cnt == partContainer.size() * (partContainer.size() - 1));
}

/**
 * \brief Method for testing if ParticleContainer::iterate_pairs_half iterates over the correct number of particle pairs.
 */
void UTest_ParticleContainer::testIteratePairHalfCount(){
	countPairs cntPairs = countPairs();
	partContainer.iterate_pairs_half(cntPairs);
	CPPUNIT_ASSERT(cntPairs.cnt == partContainer.size() * (partContainer.size() - 1) * 0.5);
}
