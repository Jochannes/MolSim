/*
 * UTestCellContainer.h
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#ifndef UTESTCELLCONTAINER_H_
#define UTESTCELLCONTAINER_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utils/Vector.h"
#include "CellContainer.h"

namespace unitTest {

class UTest_CellContainer : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE (UTest_CellContainer);
	CPPUNIT_TEST (testSize);
	CPPUNIT_TEST (testAddSize);
	CPPUNIT_TEST (testRemoveSize);
	CPPUNIT_TEST (testRemoveHalo);
	CPPUNIT_TEST (testIterateBoundaryCount);
	CPPUNIT_TEST (testIterateHaloCount);
	CPPUNIT_TEST (testIterateCount);
	CPPUNIT_TEST (testIteratePairCount);
	CPPUNIT_TEST (testIteratePairHalfCount);
	CPPUNIT_TEST_SUITE_END();

private:
	int numParticles = 100; 				//!< Number of particles with which the container will be initialized.
	int numHalo = 10; 						//!< Number of particles in the halo region with which the container will be initialized.
	utils::Vector<double, 3> domainSize;	//!< Domain size for the cell container in each dimension.
	double cutoff;							//!< Cutoff radius for the cell container.
	CellContainer cellContainer; 			//!< CellContainer for testing.

public:
	UTest_CellContainer();
	void setUp();
	void tearDown();

	void testSize();
	void testAddSize();
	void testRemoveSize();
	void testRemoveHalo();
	void testIterateBoundaryCount();
	void testIterateHaloCount();
	void testIterateCount();
	void testIteratePairCount();
	void testIteratePairHalfCount();
};

}

#endif /* UTESTCELLCONTAINER_H_ */
