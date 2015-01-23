/*
 * VelDenHandler.cpp
 *
 *  Created on: 21.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef VELDENHANDLER_H_
#define VELDENHANDLER_H_

#include "ParticleHandler.h"
#include "Particle.h"
#include "utils/Vector.h"


/**
 * \brief Class for calculating a velocity-density-profile.
 */
class VelDenHandler: public ParticleHandler
{
private:
	const int N;			//!< number of bins
	const double x_start;	//!< left edge of the first bin
	const double x_end;		//!< right edge of the last bin
	const double width;		//!< width of a bin

	double* bin_mass;	//!< array to store the mass
	double* bin_vel;	//!< array to store the velocity
	int*	bin_count;	//!< array to store the number of particles

public:
	VelDenHandler(int arg_N, double arg_x_start, double arg_x_end, double* arg_bin_mass, double* arg_bin_vel, int* arg_bin_count) :
		N(arg_N), x_start(arg_x_start), x_end(arg_x_end),
		bin_mass(arg_bin_mass), bin_vel(arg_bin_vel), bin_count(arg_bin_count),
		width( (arg_x_end - arg_x_start)/double(arg_N) ) {
	}

	virtual ~VelDenHandler() {
	}

	/**
	 * \brief Method for adding mass and velocity of each particle to the bins.
	 * This function determines in which bin the particle belongs and then adds
	 * its velocity and mass to that bin.
	 *
	 * @param p particle to calculated
	 */
	virtual void compute(Particle& p);

};


#endif /* VELDENHANDLER_H_ */
