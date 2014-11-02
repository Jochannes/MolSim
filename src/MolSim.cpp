

#include "ParticleContainer.h"
#include "ParticleInput_FileReader.h"
#include "ParticleOutput_VTK.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "handler/ForceCalculator_Gravity.h"

#include <list>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

/**** forward declaration of the calculation functions ****/

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
double start_time = 0; //!< Starting time of the simulation.
double end_time   = 1000; //!< End time of the simulation.
double delta_t    = 0.014; //!< Time step size of the simulation.

ParticleContainer	particles; //!< Container for encapsulating the particle list.
ParticleInput* 		particleIn; //!< Object for defining the input method to be used.
ParticleOutput*		particleOut; //!< Object for defining the output method to be used.

PositionCalculator*	xcalc; //!< Object for defining the coordinate calculator to be used in the simulation.
VelocityCalculator*		vcalc; //!< Object for defining the velocity calculator to be used in the simulation.
ForceCalculator*		fcalc; //!< Object for defining the force calculator to be used in the simulation.


int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	
	// parsing commandline parameters
	switch (argc)
	{
	case 4:		// 3 parameters are given.
		delta_t = atof(argsv[3]);

		if (delta_t > 0.0) {
			cout << "using parameter delta_t=" << delta_t << endl;
		} else {
			cout << "invalid parameter delta_t!" << endl;
			return 1;
		}
		/* no break */

	case 3:		// 2 parameters are given.
		delta_t = atof(argsv[2]);

		if (end_time > 0.0) {
			cout << "using parameter end_time=" << end_time << endl;
		} else {
			cout << "invalid parameter end_time!" << endl;
			return 1;
		}
		/* no break */

	case 2:		// 1 parameter is given.
		cout << "using parameter filename=\"" << argsv[1] << "\"" << endl;
		break;

	default:	// no or more than 3 parameters are given.
		cout << "Erroneous program call! " << endl;
		cout << "./MolSim filename [end_time [delta_t]]" << endl;
		return 1;
	};

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
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
	return 0;
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

