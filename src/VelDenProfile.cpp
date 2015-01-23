/*
 * VelDenProfile.cpp
 *
 *  Created on: 21.01.2015
 *      Author: Jochannes, DanielCAlbert
 */ 


#include "VelDenProfile.h"
#include "ParticleContainer/ParticleContainer.h"
#include "handler/VelDenHandler.h"

#include <fstream>
#include <log4cxx/logger.h>
#include <cstdlib>

using namespace std;
using namespace log4cxx;


LoggerPtr vdplogger(Logger::getLogger("MolSim.VelDenProfile"));


VelDenProfile::VelDenProfile(ParticleContainer* arg_cont, int arg_N, double arg_x_start, double arg_x_end,
							std::string& arg_velocity_file, std::string& arg_density_file, int arg_freq)
			:
			cont(arg_cont), N(arg_N), x_start(arg_x_start), x_end(arg_x_end),
			density_file(arg_density_file), velocity_file(arg_velocity_file),
			freq(arg_freq), width( (arg_x_end - arg_x_start)/double(arg_N) )
{
	bin_mass  = new double[N];
	bin_vel   = new double[N];
	bin_count = new int[N];

	bin_density = new double[N];
	bin_avgvel  = new double[N];

	for(int i=0; i<N; i++) {
		bin_density[i] = 0;
		bin_avgvel[i]  = 0;
	}
}


VelDenProfile::~VelDenProfile() {
	delete[] bin_mass;
	delete[] bin_vel;
	delete[] bin_count;

	delete[] bin_density;
	delete[] bin_avgvel;
}


/**
 * /brief Auxiliary function for updating the profile after an iteration.
 */
void VelDenProfile::calculate() {
	// reset bins
	for(int i=0; i<N; i++) {
		bin_mass[i]  = 0.0;;
		bin_vel[i]   = 0.0;
		bin_count[i] = 0;
	}

	// collect information from particles in the container
	VelDenHandler h(N, x_start, x_end, bin_mass, bin_vel, bin_count);
	cont->iterate_all(h);

	// calculate average of this iteration and accumulate
	for(int i=0; i<N; i++) {
		if( bin_count[i] != 0 ) {
			double count = double(bin_count[i]);

			bin_density[i] = bin_mass[i] / width;
			bin_avgvel[i]  = bin_vel[i] / count;
		}
		else {
			bin_density[i] = 0.0;
			bin_avgvel[i]  = 0.0;
		}
	}
}


/**
 * /brief Auxiliary function for writing a profile to a csv file.
 * @param bin Array/bins containing the profile information
 * @param output_file Name of the file to write to.
 */
void VelDenProfile::output(double* bin, string& output_file) {

	ofstream ofs(output_file.c_str(), fstream::out | fstream::app);
	if( !ofs.is_open() ) {
		LOG4CXX_FATAL(vdplogger, "Error writing to file: " << output_file);
		exit(1);
	}

	for(int i=0; i<(N-1); i++) {
		ofs << bin[i] << ",";
	}
	ofs << bin[N-1] << endl;


	ofs.close();

	LOG4CXX_DEBUG(vdplogger, "writing to file: " << output_file);
}


void VelDenProfile::analyse(int iteration) {

	if( (iteration % freq) == 0 ) {
		calculate();

		output(bin_density, density_file);
		output(bin_avgvel, velocity_file);
	}
}


