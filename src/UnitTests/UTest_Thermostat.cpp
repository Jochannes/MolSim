/*
 * UTest_Thermostat.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "UTest_Thermostat.h"
#include "CuboidGenerator.h"
#include "ParticleContainer/SimpleContainer.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "Thermostat.h"
#include <cstdlib>
#include <cmath>

using namespace std;


extern double delta_t;


namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_Thermostat);

/**
 * \brief Set up the unit tests.
 */
void UTest_Thermostat::setUp() {
	int z;
	if (num_dimensions == 2) {
		z = 1;
	}
	else if (num_dimensions == 3) {
		z = size;
	}
	else {
		cerr << "Error in UTEST_Thermostat: invalid value for num_dimensions." << endl;
		exit(1);
	}

	double x[3] = {0.0, 0.0, 0.0};
	int    n[3] = {size, size, z};
	double h    = 1.0;
	double m    = 1.0;
	double v[3] = {0.0, 1.0, 0.0};

	input = new CuboidGenerator(x, n, h, m, v);
}

/**
 * \brief Free the used resources.
 */
void UTest_Thermostat::tearDown() {
	delete input;
}

/**
 * \brief Tests the Thermostat in a scenario with variable temperature.
 */
void UTest_Thermostat::testTemperatureControl() {
	
	const double precision = 0.000001;	// for handling rounding errors;

	PositionCalculator xcalc;
	VelocityCalculator vcalc;
	ForceCalculator_Gravity gfcalc(-9.8);
	ForceCalculator_LennardJones ljfcalc;

	int steps_thermostat = 5;
	int steps_changetemp = 20;
	int iteration = 0;
	int max_it = 100;
	double temp = init_temp;
	::delta_t = 0.005;

	// initialize
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

	SimpleContainer particles(particleVector);
	Thermostat thermostat(particles, num_dimensions, init_temp, steps_thermostat, target_temp, delta_temp, steps_changetemp);

	particles.iterate_all(gfcalc);
	particles.iterate_all(ljfcalc);

	// perform a test "simulation"	
	while (iteration < max_it) {
		// change particles
		particles.iterate_all(xcalc);
		particles.iterate_all(gfcalc);
		particles.iterate_all(ljfcalc);
		particles.iterate_all(vcalc);

		iteration++;

		thermostat.handle(iteration);	// control temperatures

		// check targeted temperature
		if (iteration % steps_changetemp == 0) {
			temp += delta_temp;
		}
		CPPUNIT_ASSERT( temp == thermostat.next_temp );

		// check actual temperature
		if (iteration % steps_thermostat == 0) {
			double actual_temp = 2 / (Thermostat::k_B * num_dimensions * particles.size()) * thermostat.calculateKineticEnergy();
			double error = abs(actual_temp - temp);

			CPPUNIT_ASSERT( error < precision );
		}
	}
}


}
