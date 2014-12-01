/*
 * UTest_BoundaryCondition.h
 *
 *  Created on: Nov 27, 2014
 *      Author: johannes
 */

#ifndef UTEST_BOUNDARYCONDITION_H_
#define UTEST_BOUNDARYCONDITION_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utils/Vector.h"
#include "ParticleContainer/CellContainer.h"

namespace unitTest {

/**
 * \brief Class for testing the all implementations of the BoundaryCondition interface.
 */
class UTest_BoundaryCondition: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE (UTest_BoundaryCondition);
	CPPUNIT_TEST(testOutflow);
	CPPUNIT_TEST(testReflectionCnt);
	CPPUNIT_TEST_SUITE_END();

private:
	int numParticles; //!< Number of particles with which the container will be initialized.
	int numHalo; //!< Number of particles in the halo region with which the container will be initialized.
	utils::Vector<double, 3> domainSize;//!< Domain size for the cell container in each dimension.
	double cutoff;					//!< Cutoff radius for the cell container.
	CellContainer cellCont; 			//!< CellContainer for testing.

public:
	UTest_BoundaryCondition();
	void setUp();
	void tearDown();

	void testOutflow();
	void testReflectionCnt();
};

}

#endif /* UTEST_BOUNDARYCONDITION_H_ */
