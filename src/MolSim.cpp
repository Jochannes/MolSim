

#include "ParticleContainer.h"
#include "ParticleInput_FileReader.h"
#include "ParticleOutput_VTK.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator_Gravity.h"

#include <cstring>
#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

using namespace std;
using namespace log4cxx;


/**** forward declaration of the calculation functions ****/

/**
 * \brief Parse parameters.
 */
void parseParameters(int argc, char* argsv[]);

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
double start_time = 0;		//!< Starting time of the simulation.
double end_time   = 1000;	//!< End time of the simulation.
double delta_t    = 0.014;	//!< Time step size of the simulation.

ParticleContainer	particles;		//!< Container for encapsulating the particle list.
ParticleInput* 		particleIn;		//!< Object for defining the input method to be used.
ParticleOutput*		particleOut;	//!< Object for defining the output method to be used.

PositionCalculator*	xcalc; //!< Object for defining the coordinate calculator to be used in the simulation.
VelocityCalculator*	vcalc; //!< Object for defining the velocity calculator to be used in the simulation.
ForceCalculator*	fcalc; //!< Object for defining the force calculator to be used in the simulation.

LoggerPtr logger(Logger::getLogger("MolSim"));	//!< Object for handling general logs.


int main(int argc, char* argsv[]) {

	// configure logging
	PropertyConfigurator::configure("./MolSim.logging.conf");

	LOG4CXX_INFO(logger, "Hello from MolSim for PSE!");
	
	parseParameters(argc, argsv);

	// configure all handlers
	particleIn  = new ParticleInput_FileReader(particles, argsv[1]);
	particleOut = new ParticleOutput_VTK(particles, "MD_vtk");
	xcalc = new PositionCalculator();
	vcalc = new VelocityCalculator();
	fcalc = new ForceCalculator_Gravity();

	// create particles using respective input method
	particleIn->input();

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
void parseParameters(int argc, char* argsv[])
{
	switch (argc)
	{
	case 4:		// 3 parameters are given.
		delta_t = atof(argsv[3]);
		if (delta_t > 0.0) {
			LOG4CXX_DEBUG(logger, "using parameter delta_t=" << delta_t);
		} else {
			LOG4CXX_FATAL(logger, "invalid parameter delta_t!");
			exit(1);
		}
		/* no break */

	case 3:		// 2 parameters are given.
		delta_t = atof(argsv[2]);
		if (end_time > 0.0) {
			LOG4CXX_DEBUG(logger, "using parameter end_time=" << end_time);
		} else {
			LOG4CXX_FATAL(logger, "invalid parameter end_time!");
			exit(1);
		}
		/* no break */

	case 2:		// 1 parameter is given.
		LOG4CXX_DEBUG(logger, "using parameter filename=\"" << argsv[1] << "\"");
		break;

	default:	// no or more than 3 parameters are given.
		LOG4CXX_FATAL(logger, "Erroneous program call!");
		LOG4CXX_INFO(logger, "./MolSim filename [end_time [delta_t]]");
		exit(1);;
	};
}


/**
 * The forces are calculated by first resetting them to 0
 * and then using the iteration function in ParticleHandler
 * to call the force calculation method saved in `fcalc` for each particle.
 */
void calculateF() {
	// update OldF and set F to 0.0
	particles.prepare_forces();

	// calculate forces
	particles.iterate_pairs(*fcalc);
}


/**
 * The positions are calculated by using the iteration function in ParticleHandler
 * to call the position calculation method saved in `xcalc` for each particle.
 */
void calculateX() {
	particles.iterate_all(*xcalc);
}


/**
 * The velocities are calculated by using the iteration function in ParticleHandler
 * to call the velocity calculation method saved in `xcalc` for each particle.
 */
void calculateV() {
	particles.iterate_all(*vcalc);
}

/**
 * The particles for this time step are saved using
 * the function defined in the object particleOut.
 */
void plotParticles(int iteration) {
	particleOut->output(iteration);
}

