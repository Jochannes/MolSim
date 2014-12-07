/*
 * ResultOutput.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ResultOutput.h"
#include "handler/plotHandler_ResultOutput.h"
#include <log4cxx/logger.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace log4cxx;


void ResultOutput::output()
{
	static LoggerPtr roLogger(Logger::getLogger("MolSim.ResultOutput"));

	int num_particles = container.size();

	ofstream output_file(filename.c_str());
	if (!output_file.is_open()) {
		LOG4CXX_FATAL(roLogger, "Error: could not open file " << filename);
		exit(1);
	}

	output_file << setprecision(17) << num_particles << "\n";

	plotHandler_ResultOutput h(output_file);
	container.iterate_all(h);

	output_file.close();
}

