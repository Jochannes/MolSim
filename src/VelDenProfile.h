/*
 * VelDenProfile.h
 *
 *  Created on: 21.01.2015
 *      Author: Jochannes, DanielCAlbert
 */ 


#include "ParticleContainer/ParticleContainer.h"
#include <string>


/**
 * \brief Class for creating a velocity-density-profile of a particle container.
 *
 * The container is divided into N bins along the x-axis. For each Particle
 * the correct bin is calculated and its velocity and mass added to the bin.
 * The values will be accumulated over all time steps.
 */
class VelDenProfile
{
private:
	const int N;			//!< number of bins
	const double x_start;	//!< left edge of the first bin
	const double x_end;		//!< right edge of the last bin
	const double width;		//!< width of a bin

	double* bin_mass;	//!< array to store the mass
	double* bin_vel;	//!< array to store the velocity
	int*    bin_count;	//!< array to store the number of particles

	double* bin_density;	//!< array to store the accumulated density
	double* bin_avgvel;		//!< array to store the accumulated average velocity

	ParticleContainer* cont;	//!< ParticleContainer storing the particles for the analysis.

	int freq;					//!< number of time steps to wait between outputs.
	std::string velocity_file;	//!< name of the file to write the profile.
	std::string density_file;	//!< name of the file to write the profile.


	void calculate();
	void output(double* bin, std::string& output_file);

public:
	VelDenProfile(ParticleContainer* arg_cont, int arg_N, double arg_x_start, double arg_x_end,
				std::string& arg_velocity_file, std::string& arg_density_file, int arg_freq = 10000);

	~VelDenProfile();

	/**
	 * /brief Calculate and output the profile. This function should be called in every time step.
	 * @param iteration Number of the current iteration of the simulation.
	 */
	void analyse(int iteration);
};


