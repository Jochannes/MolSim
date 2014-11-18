#include "ParticleContainer.h"
#include "CellContainer.h"
#include "ParticleInput_FileReader.h"
#include "CuboidGenerator.h"
#include "ParticleOutput_VTK.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/stream.h>

//UnitTests
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "UnitTests/UTest_ParticleContainer.h"

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

ParticleContainer* particles;		//!< Container for encapsulating the particle list.
ParticleInput* particleIn = NULL; 	//!< Object for defining the input method to be used.
ParticleOutput* particleOut = NULL; //!< Object for defining the output method to be used.
PositionCalculator* xcalc = NULL; 	//!< Object for defining the coordinate calculator to be used in the simulation.
VelocityCalculator* vcalc = NULL; 	//!< Object for defining the velocity calculator to be used in the simulation.
ForceCalculator* fcalc = NULL; 		//!< Object for defining the force calculator to be used in the simulation.

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

	// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {

		calculateX(); // calculate new coordinates
		calculateF(); // calculate new forces
		calculateV(); // calculate new velocities

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		LOG4CXX_DEBUG(logger, "Iteration " << iteration << " finished.");

		current_time += delta_t;
	}

	LOG4CXX_INFO(logger, "output written. Terminating...");

	return 0;
}

/**
 * Parses the parameters from the commandline
 * and configures the program accordingly.
 */
void parseParameters(int argc, char* argsv[]) {
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

			// if a value for the option is given, set the variable
			// accordingly. Otherwise the variable is NULL.
			if ((argc > i + 1) && (argsv[i + 1][0] != '-')) {
				value = argsv[i + 1];
				i++;
			}

			if (strcmp(option, "help") == 0) {
				cout
						<< "usage: MolSim [OPTIONS]\n"
								"\n"
								"Options:\n"
								"  -delta_t VALUE	Sets the size of each time step in the simulation to VALUE.\n"
								"			The default is 0.014.\n"
								"  -end_time VALUE	Sets the time of the simulation's end to VALUE.\n"
								"			The default is 1000.\n"
								"  -cont VALUE	Specifies the container method for storage and force calculation.\n"
								"			NAME can be \"cells\" for the linked-cell algorithm or \"simple\" for a simple particle container.\n"
								"			The default is \"cells\".\n"
								"  -force NAME		Specifies the method for force calculation between the particles.\n"
								"			NAME can be \"grav\" for gravity or \"lj\" for Lennard-Jones potential.\n"
								"			The default is \"lj\".\n"
								"  -gencub FILENAME	Generates one or more cuboids of particles and adds brownian motion.\n"
								"			All necessary parameters for generation are read from a file specified by FILENAME.\n"
								"  -help			Prints this information.\n"
								"  -read FILENAME	Directly reads a set of particles from a file specified by FILENAME\n"
								"  -test [NAME]		Runs a unit test. Optionally the name of the test suite can be specified by NAME.\n"
								"\n"
								"Note:\n"
								"  You must at least use -read or -gencub once, so the simulation has particles.\n"
								"  These options can be used more than once."
								"\n" << endl;
				exit(0);
			} else if (strcmp(option, "delta_t") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option delta_t.");
					exit(1);
				}

				delta_t = atof(value);
				if (delta_t <= 0.0) {
					LOG4CXX_FATAL(logger,
							"Error! Invalid value for option delta_t.");
					exit(1);
				}

				LOG4CXX_DEBUG(logger, "using parameter delta_t=" << delta_t);
			}

			else if (strcmp(option, "end_time") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option end_time.");
					exit(1);
				}

				end_time = atof(value);
				if (end_time <= 0.0) {
					LOG4CXX_FATAL(logger,
							"Error! Invalid value for option end_time.");
					exit(1);
				}

				LOG4CXX_DEBUG(logger, "using parameter end_time=" << end_time);
			}

			else if (strcmp(option, "cont") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option cont.");
					exit(1);
				}

				if (strcmp(value, "cells") == 0) {
					//TODO Set particles as CellContainer -> xml
					LOG4CXX_DEBUG(logger, "using linked-cell algorithm.");
				} else if (strcmp(value, "simple") == 0) {
					//TODO Set particles as ParticleContainer -> xml
					LOG4CXX_DEBUG(logger,
							"using simple particle container.");
				} else {
					LOG4CXX_FATAL(logger,
							"Error! Invalid value for option cont.");
					exit(1);
				}
			}

			else if (strcmp(option, "force") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option force.");
					exit(1);
				}

				if (strcmp(value, "grav") == 0) {
					fcalc = new ForceCalculator_Gravity();
					LOG4CXX_DEBUG(logger, "using gravity force calculator.");
				} else if (strcmp(value, "lj") == 0) {
					fcalc = new ForceCalculator_LennardJones();
					LOG4CXX_DEBUG(logger,
							"using Lennard-Jones force calculator.");
				} else {
					LOG4CXX_FATAL(logger,
							"Error! Invalid value for option force.");
					exit(1);
				}
			}

			else if (strcmp(option, "gencub") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option gencube.");
					exit(1);
				}

				LOG4CXX_DEBUG(logger,
						"generating cuboid from file " << value << ".");
				CuboidGenerator in(*particles, value);
				in.input();
			}

			else if (strcmp(option, "read") == 0) {
				if (value == NULL) {
					LOG4CXX_FATAL(logger,
							"Error! Missing value for option read.");
					exit(1);
				}

				LOG4CXX_DEBUG(logger,
						"reading particles from file " << value << ".");
				ParticleInput_FileReader in(*particles, value);
				in.input();
			}

			else if (strcmp(option, "test") == 0) {
				LOG4CXX_DEBUG(logger, "starting unit test.");

				int ret_val = runUnitTest(value);
				exit(ret_val);
			}
		} else {
			LOG4CXX_INFO(logger, "Ignored parameter: " << argsv[i]);
		}
	}	// end for

	// check if there are particles
	if (particles->empty()) {
		LOG4CXX_FATAL(logger, "Error! No particles given.");
		exit(1);
	}

	// set default values for particle handlers if no value was specified.
	if (fcalc == NULL) {
		fcalc = new ForceCalculator_LennardJones();
		LOG4CXX_DEBUG(logger, "using Lennard-Jones force calculator.");
	}

	if (particleOut == NULL) {
		particleOut = new ParticleOutput_VTK(*particles, "MD_vtk");
		LOG4CXX_DEBUG(logger, "using VTKWriter for output.");
	}

	xcalc = new PositionCalculator();
	vcalc = new VelocityCalculator();
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

	// TODO: Redirect output to log4cxx?

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
 * to call the force calculation method saved in `fcalc` for each particle.
 */
void calculateF() {
	// update OldF and set F to 0.0
	particles->prepare_forces();

	// calculate forces
	particles->iterate_pairs_half(*fcalc);
}

/**
 * The positions are calculated by using the iteration function in ParticleHandler
 * to call the position calculation method saved in `xcalc` for each particle.
 */
void calculateX() {
	particles->iterate_all(*xcalc);
	if (typeid(*particles) == typeid(CellContainer)){
		((CellContainer*)particles)->update_cells();
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
	particleOut->output(iteration);
}
