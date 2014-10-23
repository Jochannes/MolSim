
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"

#include <list>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * interface for methods of force calculation between two particles
 * p is the main particle, for which the force is calculated
 * p2 is the interaction partner
 */
class ForceCalc
{
public:
	static utils::Vector<double, 3> calc(Particle& p, Particle& p2);
};

/**
 * interface for input methods
 */
class Input
{
public:
	static string read();
};

/**
 * interface for output methods
 */
class Output
{
public:
	static void write(string text);
};

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);


double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

//std::list<Particle> particles;

/**
 * container for encapsulation and iteration of the particle list
 */
class ParticleContainer {
public:
	list<Particle> particleList;
	list<Particle>::iterator molecule, molPartner;

	ParticleContainer () {
		resetIterators();
	}

	void resetIterators()
	{
		molecule = particleList.begin();
		molPartner = particleList.begin();
	}
} particles;


int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	
	// parsing commandline parameters
	if (argc < 2) {
		cout << "Erroneous program call! " << endl;
		cout << "./molsim filename [end_time [delta_t]]" << endl;
		exit(1);
	}
	else if (argc > 2) {
		double tmp = atof(argsv[2]);

		if (tmp > 0) {
			cout << "using parameter end_time=" << tmp << endl;
			end_time = tmp;
		} else {
			cout << "invalid parameter end_time!" << endl;
			exit(1);
		}
		
		if (argc > 3) {
			double tmp = atof(argsv[3]);

			if (tmp > 0) {
				cout << "using parameter delta_t=" << tmp << endl;
				delta_t = tmp;
			} else {
				cout << "invalid parameter delta_t!" << endl;
				exit(1);
			}

			if (argc > 4) {
				cout << "to many parameter!" <<endl;
				exit(1);
			}
		}
	}

	FileReader fileReader;
	fileReader.readFile(particles.particleList, argsv[1]);
	// the forces are needed to calculate x, but are not given in the input file.
	calculateF();

	double current_time = start_time;

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		calculateX();

		// calculate new f
		calculateF();
		// calculate new v
		calculateV();

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
 * calculate the gravitational force between two particles
 */
class GravityEq : ForceCalc
{
public:
	static utils::Vector<double, 3>& calc(Particle& p, Particle& p2)
	{
		// calculate distance between p1 and p2
		double distance = sqrt(	pow( (p.getX()[0] - p2.getX()[0]), 2) +
								pow( (p.getX()[1] - p2.getX()[1]), 2) +
								pow( (p.getX()[2] - p2.getX()[2]), 2) );

		double a = p.getM() * p2.getM() / pow(distance, 3);

		static utils::Vector<double, 3> F;
		for (int i=0; i<3; i++) {
			F[i] = a * (p2.getX()[i] - p.getX()[i]);
		}
		return F;
	}
};

void calculateF() {
	particles.resetIterators();

	//iterate over all particles
	while (particles.molecule != particles.particleList.end()) {
		particles.molPartner = particles.particleList.begin();
		Particle& p1 = *particles.molecule;

		p1.getOldF() = p1.getF();	// set OldF to current F.
		p1.getF()[0] = p1.getF()[1] = p1.getF()[2] = 0;	// set new F to zero.

		//iterate over the interaction partners
		while (particles.molPartner != particles.particleList.end()) {
			if (particles.molPartner != particles.molecule) {

				Particle& p2 = *particles.molPartner;
				
				utils::Vector<double, 3> F_i_j = GravityEq::calc(p1,p2);

				// calculate force for each particle, add 
				for (int i=0; i<3; i++) {
					p1.getF()[i] += F_i_j[i];
				}

			}
			++particles.molPartner;
		}
		++particles.molecule;
	}
}

void calculateX() {
	particles.resetIterators();

	//iterate over all particles
	while (particles.molecule != particles.particleList.end()) {

		Particle& p = *particles.molecule;

		double a = delta_t * delta_t / p.getM() / 2;
		
		// calculate x for each component
		for (int i=0; i<3; i++) {
			p.getX()[i] = p.getX()[i] + delta_t*p.getV()[i] + a*p.getF()[i];
		}
		
		++particles.molecule;
	}
}

void calculateV() {
	particles.resetIterators();

	//iterate over all particles
	while (particles.molecule != particles.particleList.end()) {

		Particle& p = *particles.molecule;

		double a = delta_t / p.getM() / 2;
		
		// calculate v for each component
		for (int i=0; i<3; i++) {
			p.getV()[i] = p.getV()[i] + a * (p.getF()[i] + p.getOldF()[i]);
		}
		
		++particles.molecule;
	}
}


void plotParticles(int iteration) {

	string out_name("MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(particles.particleList.size());

	particles.resetIterators();
	while (particles.molecule != particles.particleList.end()){

		Particle& p = *particles.molecule;

		writer.plotParticle(p);
		++particles.molecule;
	}

	writer.writeFile(out_name, iteration);
}


