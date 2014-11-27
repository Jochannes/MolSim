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
	double start_time = 0;
	double end_time = 1000;
	double delta_t = 0.014;

	force_calculator_type_t::value fc_type = force_calculator_type_t::lennard_jones;
	double epsilon = 5;
	double sigma = 0;

	simulation_mode_type_t::value sm_type = simulation_mode_type_t::linked_cell;
	double cutoff_radius = 3;
	double domain_size[3] = {1, 1, 0};
	boundary_type_t::value boundary[6] =
			{ boundary_type_t::outflow, boundary_type_t::outflow, boundary_type_t::outflow,
			  boundary_type_t::outflow, boundary_type_t::outflow, boundary_type_t::outflow  };

	std::vector<ParticleInput_FileReader> particle_file;
	std::vector<CuboidGenerator> cuboid;
	std::vector<SphereGenerator> sphere;

	std::string base_filename = "MD_vtk";
	int output_freq = 10;


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
		xmlfilename(param_xmlfilename)
	{ }

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

