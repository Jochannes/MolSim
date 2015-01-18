/*
 * Thermostat.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "Thermostat.h"
#include "handler/MaxwellBoltzmannHandler.h"
#include <cmath>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/stream.h>

using namespace std;
using namespace log4cxx;


LoggerPtr thermlogger(Logger::getLogger("MolSim.Thermostat"));


Thermostat::Thermostat(ParticleContainer& param_particles, int param_num_dimensions,
		double param_init_temp, int param_steps_thermostat,
		bool param_applyBrown) :
		particles(param_particles), num_dimensions(param_num_dimensions), steps_thermostat(
				param_steps_thermostat), target_temp(0.0), next_temp(
				param_init_temp), delta_temp(0.0), steps_tempchange(0), constant(
				true) {
	if (param_applyBrown) {
		applyBrown();
	}
	adjustParticleTemperatures();
}

Thermostat::Thermostat(ParticleContainer& param_particles, int param_num_dimensions,
		double param_init_temp, int param_steps_thermostat,
		double param_target_temp, double param_delta_temp,
		int param_steps_tempchange, bool param_applyBrown) :
		particles(param_particles), num_dimensions(param_num_dimensions), steps_thermostat(
				param_steps_thermostat), target_temp(param_target_temp), next_temp(
				param_init_temp), steps_tempchange(
				param_steps_tempchange), constant(false) {

	//Change sign of delta_temp to fit the required direction of temperature change
	if ((param_init_temp < target_temp && param_delta_temp > 0)
			|| (param_init_temp > target_temp && param_delta_temp < 0)) {
		delta_temp = param_delta_temp;
	} else {
		delta_temp = -param_delta_temp;
	}

	if (param_applyBrown) {
		applyBrown();
	}
	adjustParticleTemperatures();
}

Thermostat::~Thermostat() {
}

void Thermostat::handle(int iteration) {
	if (!constant && (iteration % steps_tempchange == 0)) {
		changeTemperature();
	}
	if (iteration % steps_thermostat == 0) {
		adjustParticleTemperatures();
	}
}

void Thermostat::changeTemperature() {
	if (delta_temp > 0) {
		if (target_temp - next_temp <= delta_temp)
			next_temp = target_temp;
		else
			next_temp += delta_temp;
	} else {
		if (target_temp - next_temp >= delta_temp)
			next_temp = target_temp;
		else
			next_temp += delta_temp;
	}
}

double Thermostat::calculateKineticEnergy()
{
	KineticEnergyHandler h;
	particles.iterate_all(h);
	return h.getKineticEnergy();
}


void Thermostat::applyBrown()
{
	double v_init = sqrt( k_B * next_temp / mass );

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
		LOG4CXX_DEBUG(thermlogger, "temp-adjust: T=" << next_temp << "; E_kin_D=" << E_kin_D << "; E_kin=" << E_kin << "; beta=" << beta);
	}
	else {
		LOG4CXX_DEBUG(thermlogger, "temp-adjust: too small kinetic energy!");
	}
}
