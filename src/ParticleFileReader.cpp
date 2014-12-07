/*
 * ParticleFileReader.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleFileReader.h"
#include "Particle.h"

#include <log4cxx/logger.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace log4cxx;


void ParticleFileReader::input(list<Particle>& particleList)
{
	static LoggerPtr pfrLogger(Logger::getLogger("MolSim.ParticleInput.ParticleFileReader"));

	double x[3] = { 0, 0, 0 };
	double v[3] = { 0, 0, 0 };
	double f[3] = { 0, 0, 0 };
	double old_f[3] = { 0, 0, 0 };
	double m = 0;
	double epsilon = 0;
	double sigma = 0;
	int type = 0;

	int num_particles = 0;

	ifstream input_file(filename.c_str());
	string tmp_string;

	if (input_file.is_open()) {
		do {
			getline(input_file, tmp_string);
			LOG4CXX_TRACE(pfrLogger, "Read line: " << tmp_string);
		}
		while (tmp_string.size() == 0 || tmp_string[0] == '#');

		istringstream numstream(tmp_string);
		numstream >> num_particles;
		LOG4CXX_DEBUG(pfrLogger, "Reading " << num_particles << ".");

		for(int i=0; i < num_particles; i++) {

			getline(input_file, tmp_string);
			LOG4CXX_TRACE(pfrLogger, "Read line: " << tmp_string);
			istringstream datastream(tmp_string);

			for (int j = 0; j < 3; j++) {
				datastream >> x[j];
			}
			for (int j = 0; j < 3; j++) {
				datastream >> v[j];
			}
			for (int j = 0; j < 3; j++) {
				datastream >> f[j];
			}
			for (int j = 0; j < 3; j++) {
				datastream >> old_f[j];
			}
			datastream >> m;
			datastream >> epsilon;
			datastream >> sigma;

			if (datastream.eof()  &&  (i != num_particles-1)) {
				LOG4CXX_FATAL(pfrLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
				exit(1);
			}

			datastream >> type;

			Particle p(x, v, f, old_f, m, epsilon, sigma, type);
			particleList.push_back(p);
		}
	} else {
		LOG4CXX_FATAL(pfrLogger, "Error: could not open file " << filename);
		exit(1);
	}
}


std::string ParticleFileReader::toString()
{
	std::stringstream str;

	str << "\"" << filename << "\"";

	return str.str();
}
