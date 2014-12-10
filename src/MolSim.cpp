#include "ParticleContainer/ParticleContainer.h"
#include "ParticleContainer/CellContainer.h"
#include "XMLInput/XMLInput.h"
#include "ParticleOutput.h"
#include "ResultOutput.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator.h"
#include "Thermostat.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/stream.h>
#include <typeinfo>
#include <sys/time.h>

//UnitTests
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;
using namespace log4cxx;

/**** forward declaration of the calculation functions ****/

/**
 * \brief Parse parameters.
 * @param argc number of parameters
 * @param argsv array containing the parameter c-strings
 */
void parseParameters(int argc, char* argsv[]);

/**
 * \brief Run a unit test.
 * @param test name of the test to run
 */
int runUnitTest(const char* test);

/**
 * \brief Calculate the force for all particles.
 */
void calculateF();

/**
 * \brief Calculate the position for all particles.
 */
void calculateX();

/**
 * \brief Calculate the velocity for all particles.
 */
void calculateV();

/**
 * \brief Plot the particles.
 */
void plotParticles(int iteration);

// global variables
double start_time = 0.0;	//!< Starting time of the simulation.
double end_time = 1000; 	//!< End time of the simulation.
double delta_t = 0.014; 	//!< Time step size of the simulation.
int output_freq = 10;	//!< Output frequency of the simulation.

Thermostat* thermostat;	//!< Thermostat controlling the temperatures of the particles.

ParticleContainer* particles;//!< Container for encapsulating the particle list.
ParticleOutput* particleOut = NULL; //!< Object for defining the output method to be used.
ResultOutput* resultOut = NULL;	//!< Object for defining the result output method.
PositionCalculator* xcalc = NULL; //!< Object for defining the coordinate calculator used in the simulation.
VelocityCalculator* vcalc = NULL; //!< Object for defining the velocity calculator used in the simulation.
ForceCalculator** fcalcs; //!< Object for defining the force calculators used in the simulation.
int numForceCalcs;			//!< Number of force calculators.

bool timing = false;	//!< Specifies if the iteration time will be measured.
char* timingFile;	//!< Name of the file to store the timing results.
int timingCount = 100;	//!< Number of iterations to measure.

LoggerPtr logger(Logger::getLogger("MolSim")); //!< Object for handling general logs.

int main(int argc, char* argsv[]) {

	// configure logging
	PropertyConfigurator::configure("./MolSim.logging.conf");

	LOG4CXX_INFO(logger, "Hello from MolSim for PSE!");

	parseParameters(argc, argsv);

	// the forces are needed to calculate x, but are not given in the input file.
	calculateF();


	double current_time = start_time;

	int iteration = 0;

	timeval timer_begin, timer_end;
	if (timing) {
		gettimeofday(&timer_begin, NULL);
	}

	// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {

		calculateX(); // calculate new coordinates
		calculateF(); // calculate new forces
		calculateV(); // calculate new velocities

		// control temperatures (if activated)
		if (thermostat != NULL) {
			thermostat->handle(iteration);
		}

		iteration++;

		if (iteration % output_freq == 0) {
			plotParticles(iteration);
		}
		LOG4CXX_DEBUG(logger, "Iteration " << iteration << " finished.");

		current_time += delta_t;

		if (timing && (iteration == timingCount)) {
			gettimeofday(&timer_end, NULL);

			timeval diff;
			timersub(&timer_end, &timer_begin, &diff);

			double secs = (double(diff.tv_sec)
					+ double(diff.tv_usec) / 1000000.0);
			double avg_secs = secs / double(timingCount);

			LOG4CXX_INFO(logger, "writing timing output...");

			ofstream ofs;
			ofs.open(timingFile);
			ofs << "Total time (" << timingCount << " iterations): "
					<< secs << " seconds" << endl;
			ofs << "Average time (" << timingCount << " iterations): "
					<< avg_secs << " seconds" << endl;
			ofs.close();
		}
	}

	if (timing && iteration < timingCount) {

		gettimeofday(&timer_end, NULL);
		LOG4CXX_DEBUG(logger,
				"the timer could not measure enough iterations...");

		if (iteration > 0) {
			timeval diff;
			timersub(&timer_end, &timer_begin, &diff);

			double avg_secs = (double(diff.tv_sec)
					+ double(diff.tv_usec) / 1000000.0) / double(iteration);

			LOG4CXX_INFO(logger, "writing timing output...");

			ofstream ofs;
			ofs.open(timingFile);
			ofs << "Average time (" << iteration << " iterations): " << avg_secs
					<< " seconds" << endl;
			ofs.close();
		}
	}

	if (resultOut != NULL) {
		LOG4CXX_INFO(logger, "saving result...");
		resultOut->output();
	}

	LOG4CXX_INFO(logger, "output written. Terminating...");
	return 0;
}

/**
 * Parses the parameters from the commandline
 * and configures the program accordingly.
 */
void parseParameters(int argc, char* argsv[]) {
	bool input_given = false;	// determines whether a XML file was read.

	// commandline must at least contain one parameter
	if (argc < 2) {
		LOG4CXX_FATAL(logger, "Invalid program call!");
		exit(1);
	}

	// handle options
	for (int i = 1; i < argc; i++) {
		if (argsv[i][0] == '-') {
			const char* option = argsv[i] + 1;
			const char* value = NULL;
			const char* value2 = NULL;

			// if a value for the option is given, set the variable
			// accordingly. Otherwise the variable is NULL.
			if ((argc > i + 1) && (argsv[i + 1][0] != '-')) {
				value = argsv[i + 1];
				i++;
			}
			if ((argc > i + 1) && (argsv[i + 1][0] != '-')) {
				value2 = argsv[i + 1];
				i++;
			}

			if (strcmp(option, "help") == 0) {
				cout
						<< "usage: MolSim OPTIONS...\n"
								"\n"
								"Options:\n"
								"  -help					Prints this information.\n"
								"  -sim XMLFILE				Starts a simulation with parameters read from XMLFILE.\n"
								"  -test [NAME]				Runs a unit test. Optionally the name of the test suite can be specified by NAME.\n"
								"  -timing TXTFILE [CNT] 	Activates time measurement for the first CNT iterations with output written to TXTFILE.\n"
								"\n" << endl;
			} else if (strcmp(option, "test") == 0) {
				LOG4CXX_DEBUG(logger, "starting unit test.");

				//initialize basic simulation parameters
				delta_t = 0.001;

				int ret_val = runUnitTest(value);
				exit(ret_val);
			} else if (strcmp(option, "sim") == 0) {
				if (input_given) {
					LOG4CXX_FATAL(logger,
							"Error! More than one input file specified.");
					exit(1);
				}

				LOG4CXX_DEBUG(logger, "reading parameters for simulation.");

				if (value == NULL) {
					LOG4CXX_FATAL(logger, "Error! No input file specified.");
					exit(1);
				}

				// read XML file. set global variables accordingly.
				XMLInput input(value);
				input.input();

				input_given = true;
			} else if (strcmp(option, "timing") == 0) {
				LOG4CXX_DEBUG(logger, "activating timing.");
				if (value == NULL) {
					LOG4CXX_FATAL(logger, "Error! No output file specified.");
					exit(1);
				}
				if (value2 != NULL) {
					timingCount = atoi(value2);
				}

				timing = true;
				timingFile = new char[strlen(value) + 1];
				strcpy(timingFile, value);
			}
		} else {
			LOG4CXX_INFO(logger, "Ignored parameter: " << argsv[i]);
		}
	} // end for

	if (!input_given) {
		// no simulation parameters specified, only tests or information.
		exit(0);
	}

	// check if there are any particles
	if (particles->empty()) {
		LOG4CXX_FATAL(logger, "Error! No particles given.");
		exit(1);
	}
}

/**
 * Runs a CppUnit unit test specified by parameter `test`.
 */
int runUnitTest(const char* test) {
	CppUnit::TextUi::TestRunner runner;

	//retrieve instance of TestFactoryRegistry
	CppUnit::TestFactoryRegistry &registry =
			CppUnit::TestFactoryRegistry::getRegistry();

	//retrieve test suite created by the TestFactoryRegistry
	runner.addTest(registry.makeTest());

	//check if a single test or test suite has been chosen
	if (test != NULL) {
		return runner.run(test) ? 0 : 1;
	} else {
		return runner.run() ? 0 : 1;
	}
}

/**
 * The forces are calculated by first resetting them to 0
 * and then using the iteration function in ParticleHandler
 * to call all force calculation methods saved in fcalcs for each particle.
 */
void calculateF() {
	// update OldF and set F to 0.0
	particles->prepare_forces();

	// calculate forces
	for (int i = 0; i < numForceCalcs; i++) {
		if (fcalcs[i]->interaction) {
			particles->iterate_pairs_half(*fcalcs[i]);
		} else {
			particles->iterate_all(*fcalcs[i]);
		}
	}
}

/**
 * The positions are calculated by using the iteration function in ParticleHandler
 * to call the position calculation method saved in `xcalc` for each particle.
 */
void calculateX() {
	particles->iterate_all(*xcalc);
	if (typeid(*particles) == typeid(CellContainer)) {
		((CellContainer*) particles)->update_cells();
		((CellContainer*) particles)->impose_boundConds();
	}
}

/**
 * The velocities are calculated by using the iteration function in ParticleHandler
 * to call the velocity calculation method saved in `xcalc` for each particle.
 */
void calculateV() {
	particles->iterate_all(*vcalc);
}

/**
 * The particles for this time step are saved using
 * the function defined in the object particleOut.
 */
void plotParticles(int iteration) {
	if (particleOut != NULL)
		particleOut->output(iteration);
}
