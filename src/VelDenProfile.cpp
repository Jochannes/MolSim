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
			cont(arg_cont), N(arg_N), x_start(arg_x_start), x_end(arg_x_end), density_file(arg_density_file), velocity_file(arg_velocity_file), freq(arg_freq)
{
	bin_mass = new double[N];
	bin_vel  = new double[N];
}


VelDenProfile::~VelDenProfile() {
	delete[] bin_mass;
	delete[] bin_vel;
}


/**
 * /brief Auxiliary function for updating the profile after an iteration.
 */
void VelDenProfile::calculate() {
	VelDenHandler h(N, x_start, x_end, bin_mass, bin_vel);
	cont->iterate_all(h);
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

	calculate();

	if( (iteration % freq) == 0 ) {
		output(bin_mass, density_file);
		output(bin_vel, velocity_file);
	}
}


