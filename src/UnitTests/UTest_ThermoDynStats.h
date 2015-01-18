/*
 * UTest_ThermoDynStats.h
 *
 *  Created on: Jan 18, 2015
 *      Author: johannes
 */

#ifndef UTEST_THERMODYNSTATS_H_
#define UTEST_THERMODYNSTATS_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "ThermoDynStats.h"
#include "ParticleContainer/SimpleContainer.h"

namespace unitTest {

/**
 * \brief Class for testing the calculation of thermodynamic statistics in the class ThermoDynStats.
 *
 * For this, the number of neigbours at a specific distance
 * and the average travelled distance are estimated and
 * calculated in a simple scenario.
 */
class UTest_ThermoDynStats : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( UTest_ThermoDynStats );
	CPPUNIT_TEST(testAnalyze);
	CPPUNIT_TEST_SUITE_END();

private:
	ThermoDynStats* stats;		//!< Thermodynamical statistics calculator.
	SimpleContainer* particles;	//!< Particle Container used for all calculations.
	double vel;					//!< Velocity of all particles.
	double dist;				//!< Distance between all particles.

	int analyzeFreq;			//!< Specifies how often thermodynamical statistics will be calculated.
	int avgOver;				//!< Specifies over how many iterations the statistics will be averaged.

	string varFile;				//!< Name of the file to store the movement variance.

	double dr;					//!< Radius discretization length for the radial pair distribution function.
	double maxrad;				//!< Maximum radius for the radial pair distribution function (usually the cutoff radius).
	string rdfFile;				//!< Name of the file to store the radial pair distribution function.

public:
	UTest_ThermoDynStats() :
		analyzeFreq(20), avgOver(5), dr(0.1), maxrad(3.0), varFile("test_var.csv"), rdfFile("test_rdf.csv"), vel(10), dist(2.0) {
		stats = new ThermoDynStats(analyzeFreq, avgOver, dr, maxrad, varFile, rdfFile);
	}

	void setUp();
	void tearDown();
	void testAnalyze();

};

} /* namespace UnitTest */

#endif /* UTEST_THERMODYNSTATS_H_ */
