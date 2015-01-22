/*
 * UTest_ForceCalculator_Harmonic.cpp
 *
 *  Created on: 07.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#include "UTest_ForceCalculator_Harmonic.h"
#include "utils/Vector.h"
#include "MembraneGenerator.h"

#include <vector>
#include <list>

using namespace std;
using namespace utils;


namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_ForceCalculator_Harmonic);

void UTest_ForceCalculator_Harmonic::setUp() {
}

/**
 * \brief Free the used resources.
 */
void UTest_ForceCalculator_Harmonic::tearDown() {
}

/**
 * \brief Method for testing the force calculated by ForceCalculator_Harmonic
 *
 * It is tested whether the direct and diagonal forces are repulsive
 * or attracting when the particles are in the right distance.
 */
void UTest_ForceCalculator_Harmonic::testForce() {

	p[0].getX() = 0.0;
	p[1].getX() = 0.0;
	p[2].getX() = 0.0;


	// test force = 0
	p[0].getF() = 0;
	p[1].getX()[1] = r;
	p[2].getX()[0] = r;
	p[2].getX()[1] = r;

	fHarm.calc_direct(p[0], p[1]);
	Vector<double, 3> force_direct1( p[0].getF() );

	fHarm.calc_diag(p[0], p[2]);
	Vector<double, 3> force_diag1( p[0].getF() );

	CPPUNIT_ASSERT( force_direct1.L2Norm() < pow(10, -12) );
	CPPUNIT_ASSERT( force_diag1.L2Norm() < pow(10, -12) );


	// test force < 0
	p[0].getF() = 0;
	p[1].getX()[1] = r/2;
	p[2].getX()[0] = r/2;
	p[2].getX()[1] = r/2;

	fHarm.calc_direct(p[0], p[1]);
	Vector<double, 3> force_direct2( p[0].getF() );

	fHarm.calc_diag(p[0], p[2]);
	Vector<double, 3> force_diag2( p[0].getF() );

	CPPUNIT_ASSERT( force_direct2[1] < -pow(10, -12) );
	CPPUNIT_ASSERT( force_diag2[0] < -pow(10, -12)  &&  force_diag2[1] < -pow(10, -12) );


	// test force > 0
	p[0].getF() = 0;
	p[1].getX()[1] = 2*r;
	p[2].getX()[0] = 2*r;
	p[2].getX()[1] = 2*r;

	fHarm.calc_direct(p[0], p[1]);
	Vector<double, 3> force_direct3( p[0].getF() );

	fHarm.calc_diag(p[0], p[2]);
	Vector<double, 3> force_diag3( p[0].getF() );

	CPPUNIT_ASSERT( force_direct3[1] > pow(10, -12) );
	CPPUNIT_ASSERT( force_diag3[0] > pow(10, -12)  &&  force_diag3[1] > pow(10, -12) );
}


} /* namespace unitTest */
