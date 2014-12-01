/*
 * Thermostat.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "Thermostat.h"
#include "handler/MaxwellBoltzmannHandler.h"
#include <cmath>


Thermostat::Thermostat(ParticleContainer& param_particles, int param_num_dimensions, int param_steps_thermostat, bool applyBrown)
	:
		particles(param_particles), num_dimensions(param_num_dimensions), steps_thermostat(param_steps_thermostat),
		target_temp(0.0), delta_temp(0.0), steps_tempchange(0), constant(true)
{
	double E_kin = calculateKineticEnergy();
	int num_particles = particles.size();

	if(applyBrown) {
		double v_init = sqrt( 2 * E_kin / (num_particles * num_dimensions * mass) );

		MaxwellBoltzmannHandler h(v_init, num_dimensions);
		particles.iterate_all(h);
	}

	next_temp = 2 * E_kin / (num_particles * num_dimensions * k_B);
}


Thermostat::Thermostat(ParticleContainer& param_particles, int param_num_dimensions, int param_steps_thermostat,
						double param_target_temp, double param_delta_temp, int param_steps_tempchange, bool applyBrown)
	:
		particles(param_particles), num_dimensions(param_num_dimensions), steps_thermostat(param_steps_thermostat),
		target_temp(param_target_temp), delta_temp(param_delta_temp), steps_tempchange(param_steps_tempchange), constant(false)
{
	double E_kin = calculateKineticEnergy();
	int num_particles = particles.size();

	if(applyBrown) {
		double v_init = sqrt( 2 * E_kin / (num_particles * num_dimensions * mass) );

		MaxwellBoltzmannHandler h(v_init, num_dimensions);
		particles.iterate_all(h);
	}

	next_temp = 2 * E_kin / (num_particles * num_dimensions * k_B);
}


void Thermostat::adjustParticleTemperatures()
{
	double E_kin = calculateKineticEnergy();
	int num_particles = particles.size();

	// targeted kinetic energy
	double E_kin_D = num_dimensions * num_particles * 0.5 * k_B * next_temp;

	// calculate scaling factor
	double beta = sqrt( E_kin_D / E_kin );

	// scale the temperatures of all particles
	TemperatureAdjustHandler h(beta);
	particles.iterate_all(h);
}


