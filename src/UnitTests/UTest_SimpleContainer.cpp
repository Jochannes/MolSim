/*
 * UTest_ParticleContainer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: johannes
 */

#include "UTest_SimpleContainer.h"

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "Handler/Marker.h"
#include "Handler/CountParticles.h"
#include "Handler/CountPairs.h"

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_SimpleContainer);

/**
 * \brief Set up a particle container.
 *
 * The particle container is set up with UTest_ParticleContainer::numParticles particles.
 */
void UTest_SimpleContainer::setUp() {
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;
	Particle p;
	std::vector<Particle> initialParticleList;
	for (int i = 0; i < numParticles; i++) {
		p = Particle(x, v, m);
		initialParticleList.push_back(p);
	}
	partContainer = SimpleContainer(initialParticleList);
}

/**
 * \brief Free the used resources.
 */
void UTest_SimpleContainer::tearDown() {
}

/**
 * \brief Method for testing if ParticleContainer::size returns the correct number of particles.
 */
void UTest_SimpleContainer::testSize() {
	CPPUNIT_ASSERT(numParticles == partContainer.size());
}

/**
 * \brief Method for testing if ParticleContainer::add adds the correct number of particles.
 */
void UTest_SimpleContainer::testAddSize() {

	//set up a particle
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;
	Particle p;

	//Test the addition of a single particle
	p = Particle(x, v, m);
	partContainer.add(p);
	CPPUNIT_ASSERT(numParticles + 1 == partContainer.size());

	//Test the addition of a particle list
	std::vector<Particle> lsPart;
	for (int i = 0; i < numParticles; i++) {
		p = Particle(x, v, m);
		lsPart.push_back(p);
	}
	partContainer.add(lsPart);
	CPPUNIT_ASSERT(2 * numParticles + 1 == partContainer.size());
}

/**
 * \brief Method for testing if ParticleContainer::iterate_all reaches all particles.
 */
void UTest_SimpleContainer::testIterateAll() {
	Marker marker = Marker();
	partContainer.iterate_all(marker);
	std::vector<Particle>::iterator it = partContainer.particleList.begin();
	while (it != partContainer.particleList.end()) {
		CPPUNIT_ASSERT(it->getV() == 1000);
		it++;
	}
}

/**
 * \brief Method for testing if ParticleContainer::iterate_all iterates over the correct number of particles.
 */
void UTest_SimpleContainer::testIterateCount() {
	CountParticles cntPart = CountParticles();
	partContainer.iterate_all(cntPart);
	CPPUNIT_ASSERT(cntPart.cnt == partContainer.size());
}

/**
 * \brief Method for testing if ParticleContainer::iterate_pairs iterates over the correct number of particle pairs.
 */
void UTest_SimpleContainer::testIteratePairCount() {
	CountPairs cntPairs = CountPairs();
	partContainer.iterate_pairs(cntPairs);
	CPPUNIT_ASSERT(
			cntPairs.cnt == partContainer.size() * (partContainer.size() - 1));
}

/**
 * \brief Method for testing if ParticleContainer::iterate_pairs_half iterates over the correct number of particle pairs.
 */
void UTest_SimpleContainer::testIteratePairHalfCount() {
	CountPairs cntPairs = CountPairs();
	partContainer.iterate_pairs_half(cntPairs);
	CPPUNIT_ASSERT(
			cntPairs.cnt
					== partContainer.size() * (partContainer.size() - 1) * 0.5);
}

}
