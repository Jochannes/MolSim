/*
 * UTest_ParticleFile.h
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef UTEST_PARTICLEFILE_H_
#define UTEST_PARTICLEFILE_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Particle.h"

#include <string>
#include <list>


namespace unitTest {

/**
 * \brief Class for testing ParticleFileReader and ResultOutput.
 *
 * This TestFixture will create a few particles,
 * write them to a file, read them again from that file
 * and then check whether the particles are the same.
 *
 */
class UTest_ParticleFile: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( UTest_ParticleFile );
	CPPUNIT_TEST(testIO);
	CPPUNIT_TEST_SUITE_END();

private:
	std::string filename;	//!< Name of the testfile
	std::vector<Particle> pList;	//!< List of particles to start the test with

public:
	UTest_ParticleFile()
		: filename("utest_particlefile.txt")
	{ }

	void setUp();
	void tearDown();
	void testIO();
};

}

#endif /* UTEST_PARTICLEFILE_H_ */

