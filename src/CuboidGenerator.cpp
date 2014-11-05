/*
 * CuboidGenerator.cpp
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */


#include "CuboidGenerator.h"
#include "MaxwellBoltzmannDistribution.h"
#include "utils/Vector.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;


LoggerPtr CGLogger(Logger::getLogger("MolSim.ParticleInput.CuboidGenerator"));


void generateCuboid(list<Particle>& particleList,
					utils::Vector<double, 3> corner_positions,
					int num_particles[3],
					double distance,
					double mass,
					utils::Vector<double, 3> velocity,
					double brown_factor = 0.1)
{
	LOG4CXX_DEBUG(CGLogger, "generating cuboid: x=" << corner_positions.toString() <<
			"; n=[" << num_particles[0] << ";" << num_particles[1] << ";" << num_particles[2] <<
			"]; h=" << distance << "; m=" << mass << "; v=" << velocity.toString() <<
			"; brown_factor=" << brown_factor);

	utils::Vector<double, 3> x;
	x[0] = corner_positions[0];		// set first coordinate

	for(int i = 0; i < num_particles[0]; i++) {
		x[1] = corner_positions[1];		// reset second coordinate

		for(int j = 0; j < num_particles[1]; j++) {
			x[2] = corner_positions[2];		// reset third coordinate

			for(int k = 0; k < num_particles[2]; k++) {
				// create a new Particle
				Particle p(x, velocity, mass);

				// add brownian motion
				MaxwellBoltzmannDistribution(p, brown_factor, 3);

				// add particle to ParticleContainer
				particleList.push_back(p);

				x[2] = x[2] + distance;
			}
			x[1] = x[1] + distance;
		}
		x[0] = x[0] + distance;
	}
}


void CuboidGenerator::input()
{
	int    num_cuboids = 0;
	double corner_position[3] = {0.0, 0.0, 0.0};
	int    num_particles[3] = {0, 0, 0};
	double distance = 0.0;
	double mass = 0.0;
	double velocity[3] = {0.0, 0.0, 0.0};

	ifstream input_file(filename);
	string tmp_string;

	if(input_file.is_open()) {

		getline(input_file, tmp_string);
	   	LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);

	   	// ignore empty lines and comments
	   	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
	   		getline(input_file, tmp_string);
	   		LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);
	   	}

	   	istringstream numstream(tmp_string);
	   	numstream >> num_cuboids;
	   	LOG4CXX_DEBUG(CGLogger, "Reading " << num_cuboids << ".");

	   	getline(input_file, tmp_string);
	   	LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);

	   	for (int i = 0; i < num_cuboids; i++) {
	   		istringstream datastream(tmp_string);

	   		for (int j = 0; j < 3; j++) {
	   			datastream >> corner_position[j];
	   	    }
	   	    for (int j = 0; j < 3; j++) {
	   	    	datastream >> num_particles[j];
	   	    }
	   	    datastream >> distance;

	   	    datastream >> mass;

	   	    for (int j = 0; j < 3; j++) {
	   	    	datastream >> velocity[j];
	   	    }

	   	    if (datastream.eof()) {
	   	    	LOG4CXX_FATAL(CGLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
	   	    	exit(-1);
	   	    }

	   	    generateCuboid(container.particleList, corner_position, num_particles, distance, mass, velocity);

	   	    getline(input_file, tmp_string);
	   	    LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);
	   	}
	}
	else {
		LOG4CXX_FATAL(CGLogger, "Error: could not open file " << filename);
		exit(-1);
	}
}

