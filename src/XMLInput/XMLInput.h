/*
 * XMLInput.h
 *
 *  Created on: 21.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef XMLINPUT_H_
#define XMLINPUT_H_

#include "ParticleInput_FileReader.h"
#include "CuboidGenerator.h"
#include "SphereGenerator.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "handler/ForceCalculator_LJ_cutoff.h"
#include "Thermostat.h"
#include "XMLInput/simulation.h"

#include <string>
#include <vector>

/**
 * \brief Class for reading all information for the simulation from a XML file.
 *
 */
class XMLInput {

private:
	const char* xmlfilename;

	// values specified by the XML file:
	double start_time;
	double end_time;
	double delta_t;

	std::vector<ForceCalculator_LennardJones> lennard_jones;
	std::vector<ForceCalculator_LJ_cutoff> lj_cutoff;
	std::vector<ForceCalculator_Gravity> gravity;
	int forceCalcCnt;

	simulation_mode_type_t::value sm_type;
	double cutoff_radius;
	double domain_size[3];
	boundary_type_t::value boundary[6];

	int dim;
	double init_temp;
	int steps;
	double target_temp;
	double delta_temp;
	int steps_changetemp;
	bool applyBrown;

	std::vector<ParticleInput_FileReader> particle_file;
	std::vector<CuboidGenerator> cuboid;
	std::vector<SphereGenerator> sphere;

	std::string base_filename;
	int output_freq;

	/**
	 * \brief Reads the XML file specified by 'xmlfilename' and sets the member variables accordingly.
	 */
	void ReadFile();

	/**
	 * \brief Configures the application using the member variables of this object.
	 */
	void configureApplication();

public:
	/**
	 * \brief Sets the name of the XML file.
	 *
	 * @param param_xmlfilename Name of the XML file to read.
	 */
	XMLInput(const char* param_xmlfilename) :
			xmlfilename(param_xmlfilename), start_time(0), end_time(1000), delta_t(0.014), forceCalcCnt(0),
			sm_type(simulation_mode_type_t::linked_cell), cutoff_radius(3),
			dim(0), init_temp(0), steps(0), target_temp(0), delta_temp(0), steps_changetemp(0), applyBrown(true),
			output_freq(10), base_filename("MD_vtk")
	{
		domain_size[0] = 1;
		domain_size[1] = 1;
		domain_size[2] = 0;
		for (int i = 0; i < 6; i++) {
			boundary[i] = boundary_type_t::outflow;
		}
	}

	~XMLInput() {
	}

	/**
	 * \brief Reads the XML file and configures the application accordingly.
	 *
	 */
	void input() {
		ReadFile();
		configureApplication();
	}

};

#endif /* XMLINPUT_H_ */

