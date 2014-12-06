/*
 * Thermostat.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "Thermostat.h"
#include "handler/MaxwellBoltzmannHandler.h"
#include <cmath>

#include <iostream>
using namespace std;


double Thermostat::calculateKineticEnergy()
{
	KineticEnergyHandler h;
	particles.iterate_all(h);
	return h.getKineticEnergy();
}


void Thermostat::applyBrown()
{
	double E_kin = calculateKineticEnergy();
	int num_particles = particles.size();

	double v_init = sqrt( 2 * E_kin / (num_particles * num_dimensions * mass) );

	MaxwellBoltzmannHandler h(v_init, num_dimensions);
	particles.iterate_all(h);
}


void Thermostat::adjustParticleTemperatures()
{
	double E_kin = calculateKineticEnergy();

	if (E_kin > 0.0) {
		int num_particles = particles.size();

		// targeted kinetic energy
		double E_kin_D = num_dimensions * num_particles * 0.5 * k_B * next_temp;

		// calculate scaling factor
		double beta = sqrt( E_kin_D / E_kin );

		// scale the temperatures of all particles
		TemperatureAdjustHandler h(beta);
		particles.iterate_all(h);

		cout << "temp-adjust: E_kin_D=" << E_kin_D << "; E_kin=" << E_kin << "; beta=" << beta << endl;
	}
	else {
		cout << "temp-adjust: too small kinetic energy!" << endl;
	}
}


