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

		LOG4CXX_DEBUG(thermlogger, "temp-adjust: E_kin_D=" << E_kin_D << "; E_kin=" << E_kin << "; beta=" << beta);
	}
	else {
		LOG4CXX_DEBUG(thermlogger, "temp-adjust: too small kinetic energy!");
	}
}


