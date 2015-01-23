/*
 * XMLInput.h
 *
 *  Created on: 21.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef XMLINPUT_H_
#define XMLINPUT_H_

#include "ParticleFileReader.h"
#include "CuboidGenerator.h"
#include "SphereGenerator.h"
#include "MembraneGenerator.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "handler/ForceCalculator_LJ_smoothed.h"
#include "handler/ForceCalculator_Harmonic.h"
#include "handler/ForceCalculator_Constant.h"
#include "Thermostat.h"
#include "ThermoDynStats.h"
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

	//ForceCalculators
	std::vector<ForceCalculator_LennardJones> lennard_jones;
	std::vector<ForceCalculator_LJ_smoothed> lj_smoothed;
	std::vector<ForceCalculator_Gravity> gravity;
	std::vector<ForceCalculator_Harmonic> harmonic;
	std::vector<ForceCalculator_Constant> constant_force;
	int forceCalcCnt;
	int typesCnt;

	simulation_mode_type_t::value sm_type;
	double cutoff_radius;
	double domain_size[3];
	boundary_type_t::value boundary[6];

	//Thermostat
	int dim;
	double init_temp;
	int steps;
	double target_temp;
	double delta_temp;
	int steps_changetemp;
	bool applyBrown;
	int therm_direction, therm_type;

	//ThermodynStats
	bool thdyn_use;
	int thdyn_freq, thdyn_avgover;
	double thdyn_dr, thdyn_maxrad;
	std::string thdyn_varfile, thdyn_rdffile;

	// fixed
	int fixed_count;
	int* fixed_types;

	// VelDenProfile
	bool vlp_use;
	double vlp_x_start, vlp_x_end;
	int vlp_x_count, vlp_freq;
	std::string vlp_vfile, vlp_dfile;

	std::vector<ParticleFileReader> particle_file;
	std::vector<CuboidGenerator> cuboid;
	std::vector<SphereGenerator> sphere;
	std::vector<MembraneGenerator> membrane;

	std::string base_filename;
	int output_freq;
	std::string res_filename;

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
			therm_direction(-1), therm_type(-1), fixed_count(0), fixed_types(NULL), vlp_use(false),
			output_freq(10), base_filename(""), res_filename(""), thdyn_use(false)
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

