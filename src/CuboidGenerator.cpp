/*
 * CuboidGenerator.cpp
 *
 *  Created on: 04.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "CuboidGenerator.h"

using namespace std;
using namespace log4cxx;


LoggerPtr CGLogger(Logger::getLogger("MolSim.ParticleInput.CuboidGenerator"));

/**
 * \brief Private function for generating a cuboid.
 *
 * @particleList List in which the generated particles are saved.
 * @corner_position Position of lower left front-side corner.
 * @num_particles Number of particles in all three dimensions.
 * @distance Distance between two particles (lattice constant).
 * @mass Mass of a single particle.
 * @velocity Main velocity of all particles. The velocity will be superposed by Brownian motion.
 * @brown_factor Mean velocity of the Brownian motion.
 */
void CuboidGenerator::generateCuboid(list<Particle>& particleList,
					utils::Vector<double, 3> corner_position,
					int num_particles[3],
					double distance,
					double mass,
					utils::Vector<double, 3> velocity,
					double brown_factor)
{
	LOG4CXX_DEBUG(CGLogger, "generating cuboid: x=" << corner_position.toString() <<
			"; n=[" << num_particles[0] << ";" << num_particles[1] << ";" << num_particles[2] <<
			"]; h=" << distance << "; m=" << mass << "; v=" << velocity.toString() <<
			"; brown_factor=" << brown_factor);

	utils::Vector<double, 3> x;
	x[0] = corner_position[0];		// set first coordinate

	for(int i = 0; i < num_particles[0]; i++) {
		x[1] = corner_position[1];		// reset second coordinate

		for(int j = 0; j < num_particles[1]; j++) {
			x[2] = corner_position[2];		// reset third coordinate

			for(int k = 0; k < num_particles[2]; k++) {
				// create a new Particle
				Particle p(x, velocity, mass);

				// add brownian motion
				MaxwellBoltzmannDistribution(p, brown_factor, 3);

				// add particle to the passed particle list
				particleList.push_back(p);

				x[2] = x[2] + distance;
			}
			x[1] = x[1] + distance;
		}
		x[0] = x[0] + distance;
	}
}

/**
 * \brief Read input from a file.
 *
 * Reads all lines from the file specified in the constructor
 * and saves them in the ParticleContainer specified in the constructor.
 */
void CuboidGenerator::input()
{
	std::list<Particle> genParticles;	// temporary list to store the generated particles

	int    num_cuboids = 0;
	double corner_position[3] = {0.0, 0.0, 0.0};
	int    num_particles[3] = {0, 0, 0};
	double distance = 0.0;
	double mass = 0.0;
	double velocity[3] = {0.0, 0.0, 0.0};

	ifstream input_file(filename);
	string tmp_string;

	if(input_file.is_open()) {

	   	// ignore empty lines and comments
	   	do {
	   		getline(input_file, tmp_string);
	   		LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);
	   	}
	   	while (tmp_string.size() == 0 || tmp_string[0] == '#');

	   	//read in the number of cuboids
	   	istringstream numstream(tmp_string);
	   	numstream >> num_cuboids;
	   	LOG4CXX_DEBUG(CGLogger, "Reading " << num_cuboids << ".");

	   	//read in the cuboids
	   	for (int i = 1; i <= num_cuboids; i++) {

		   	getline(input_file, tmp_string);
		   	LOG4CXX_TRACE(CGLogger, "Read line: " << tmp_string);

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

	   	    //unexpected end?
	   	    if (i != num_cuboids && datastream.eof()) {
	   	    	LOG4CXX_FATAL(CGLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
	   	    	exit(-1);
	   	    }

	   	    generateCuboid(genParticles, corner_position, num_particles, distance, mass, velocity);
	   	}
	}
	else {
		LOG4CXX_FATAL(CGLogger, "Error: could not open file " << filename);
		exit(-1);
	}

	container.add(genParticles);
}

