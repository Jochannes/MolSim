/*
 * Thermostat.h
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef THERMOSTAT_H_
#define THERMOSTAT_H_


#include "ParticleContainer/ParticleContainer.h"
#include "handler/TemperatureAdjustHandler.h"
#include "handler/KineticEnergyHandler.h"

/**
 * /brief A Thermostat controlling the temperatures of a ParticleContainer.
 *
 */
class Thermostat
{
private:
	ParticleContainer& particles;

	const int num_dimensions;		//!< number of dimensions
	const int steps_thermostat;		//!< number of time steps after which the thermostat is applied

	double target_temp;				//!< temperature of the particles the thermostat is targeting
	double next_temp;				//!< temperature of the particles the thermostat will apply in the next step.
	const bool constant;			//!< determines whether the target temperature is constant.
	const int steps_tempchange;		//!< number of timesteps after which the temperature is changed
	const double delta_temp;		//!< step size in which the temperature is changed

	const double mass = 1.0;		//!< mass of the particles

	/**
	 * /brief Auxilliary function for calculating the kinetic energy of all particles.
	 *
	 * @return The kinetic energy of all particles in the ParticleContainer.
	 */
	double calculateKineticEnergy() {
		KineticEnergyHandler h;
		particles.iterate_all(h);
		return h.getKineticEnergy();
	}

public:
	static const double k_B = 1.3806488;

	Thermostat(ParticleContainer& param_particles, int param_num_dimensions, int param_steps_thermostat,
				bool applyBrown = true);

	Thermostat(ParticleContainer& param_particles, int param_num_dimensions, int param_steps_thermostat,
				double param_target_temp, double param_delta_temp, int param_steps_tempchange,
				bool applyBrown = true);

	~Thermostat();

	/**
	 * /brief Changes the next temperature and adjusts the particle temperatures when the right time has come.
	 *
	 * @param iteration The number of the current iteration of the simulation.
	 */
	void handle(int iteration) {
		if ( !constant  &&  (iteration % steps_tempchange == 0)) {
			changeTemperature();
		}
		if (iteration % steps_thermostat == 0) {
			adjustParticleTemperatures();
		}
	}

	/**
	 * /brief Changes the next temperature using 'delta_temp'.
	 * This method should be called after 'steps_tempchange' time steps have passed.
	 */
	void changeTemperature() {
		if(next_temp != target_temp)
			next_temp += delta_temp;
	}

	/**
	 * /brief Adjusts the temperatures of all particles to match the target temperature.
	 * This method should be called after 'steps_thermostat' time steps have passed.
	 */
	void adjustParticleTemperatures();
};


#endif /* THERMOSTAT_H_ */
