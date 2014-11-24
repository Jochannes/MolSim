/*
 * XMLInput.cpp
 *
 *  Created on: 21.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "XMLInput.h"

#include "ParticleContainer.h"
#include "CellContainer.h"
#include "ParticleInput_FileReader.h"
#include "CuboidGenerator.h"
#include "ParticleOutput_VTK.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "global.h"
#include "utils/Vector.h"
#include "simulation.h"

#include <log4cxx/logger.h>
#include <auto_ptr.h>
#include <list>
#include <string>


using namespace std;
using namespace log4cxx;


void XMLInput::ReadFile(const char* filename)
{
	LoggerPtr xmllogger(Logger::getLogger("MolSim.XMLInput"));

	LOG4CXX_INFO(xmllogger, "parsing XML-file \"" << filename << "\"");

	auto_ptr<simulation_t> s;

	// parse XML file and create data structures
	try {
		s = simulation(filename);
	}
	catch (const xml_schema::exception& e) {
		LOG4CXX_FATAL(xmllogger, "Error reading XML-file: " << e);
		exit(1);
	}
	

	// 1: element "parameter"
	const simulation_parameters_t& param = s->parameter();

	// 1.1: start_time
	::start_time = param.start_time();
	LOG4CXX_DEBUG(xmllogger, "reading start_time=" << ::start_time);

	// 1.2: end_time
	::end_time = param.end_time();
	LOG4CXX_DEBUG(xmllogger, "reading end_time=" << ::end_time);

	// 1.3: delta_t
	::delta_t = param.delta_t();
	if( ::delta_t > 0 ) {
		LOG4CXX_DEBUG(xmllogger, "reading delta_t=" << ::delta_t);
	} else {
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for delta_t.");
		exit(1);
	}

	// 1.4: force-calculator
	const force_calculator_t& fc = param.force_calculator();
	
	// 1.4.1: type
	const force_calculator_type_t& fc_type = fc.type();
	const force_calculator_type_t::value fc_type_enum = fc_type;

	switch( fc_type_enum ) {
	case force_calculator_type_t::gravity: {
			LOG4CXX_DEBUG(xmllogger, "using gravity force calculator.");
			fcalc = new ForceCalculator_Gravity();
		}
		break;

	case force_calculator_type_t::lennard_jones: {
			double arg_epsilon = 5.0;
			double arg_sigma = 1.0;

			LOG4CXX_DEBUG(xmllogger, "using Lennard-Jones force calculator.");
			
			// 1.4.2: epsilon
			const force_calculator_t::epsilon_optional& epsilon = fc.epsilon();
			if (epsilon.present()) {
				arg_epsilon = epsilon.get();
				LOG4CXX_DEBUG(xmllogger, "reading epsilon=" << arg_epsilon);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no epsilon specified for force calculation");
				// using default value
			}
			
			// 1.4.3: sigma
			const force_calculator_t::sigma_optional& sigma = fc.sigma();
			if (sigma.present()) {
				arg_sigma = sigma.get();
				LOG4CXX_DEBUG(xmllogger, "reading sigma=" << arg_sigma);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no sigma specified for force calculation.");
				// using default value.
			}

			ForceCalculator_LennardJones::epsilon = arg_epsilon;
			ForceCalculator_LennardJones::sigma   = arg_sigma;
			fcalc = new ForceCalculator_LennardJones();
		}
		break;
	
	default:
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for force calculator type!");
		exit(1);
	};


	// 1.5: simulation-mode
	const simulation_mode_t& sm = param.simulation_mode();
	
	// 1.4.1: type
	const simulation_mode_type_t& sm_type = sm.type();
	const simulation_mode_type_t::value sm_type_enum = sm_type;

	switch( sm_type_enum ) {
	case simulation_mode_type_t::normal: {
			LOG4CXX_DEBUG(xmllogger, "using normal simulation mode.");
			::particles = new ParticleContainer();
		}
		break;

	case simulation_mode_type_t::linked_cell: {
			double arg_cutoff_radius;
			double arg_domain_size[3] = {1, 1, 1};

			LOG4CXX_DEBUG(xmllogger, "using Linked-Cell simulation mode.");
			
			// 1.4.2: cutoff_radius
			const simulation_mode_t::cutoff_radius_optional& cutoff_radius = sm.cutoff_radius();
			if (cutoff_radius.present()) {
				arg_cutoff_radius = cutoff_radius.get();
				LOG4CXX_DEBUG(xmllogger, "reading cutoff_radius=" << arg_cutoff_radius);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no cutoff_radius specified for Linked-Cell-mode.");
				// using default value.
			}
			
			// 1.4.3: domain_size_x
			const simulation_mode_t::domain_size_x_optional& domain_size_x = sm.domain_size_x();
			if (domain_size_x.present()) {
				arg_domain_size[0] = domain_size_x.get();
				LOG4CXX_DEBUG(xmllogger, "reading domain_size_x=" << arg_domain_size[0]);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no domain_size_x specified for Linked-Cell-mode.");
				// using default value.
			}
			
			// 1.4.4: domain_size_y
			const simulation_mode_t::domain_size_y_optional& domain_size_y = sm.domain_size_y();
			if (domain_size_y.present()) {
				arg_domain_size[1] = domain_size_y.get();
				LOG4CXX_DEBUG(xmllogger, "reading domain_size_y=" << arg_domain_size[1]);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no domain_size_y specified for Linked-Cell-mode.");
				// using default value.
			}

			// TODO: use CellContainer...
			//::particles = new CellContainer(arg_domain_size, arg_cutoff_radius);
		}
		break;
	
	default:
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for simulation mode type!");
		exit(1);
	};


	// 2: element "input"
	const simulation_input_t& in = s->input();
	list<Particle> particleList;

	// 2.1: element "particle_file"
	for( simulation_input_t::particle_file_const_iterator it = in.particle_file().begin();
		 it != in.particle_file().end();
		 it++ )
	{
		ParticleInput_FileReader input(particleList, it->c_str());

		LOG4CXX_DEBUG(xmllogger, "reading particle file \"" << it->c_str() << "\"");
		input.input();
	}
	
	// 2.2: element "cuboid_file"
	for( simulation_input_t::cuboid_file_const_iterator it = in.cuboid_file().begin();
		 it != in.cuboid_file().end();
		 it++ )
	{
		CuboidGenerator input(particleList, it->c_str());

		LOG4CXX_DEBUG(xmllogger, "reading cuboid file \"" << it->c_str() << "\"");
		input.input();
	}
	
	// 2.3: element "sphere_file"
	for( simulation_input_t::sphere_file_const_iterator it = in.sphere_file().begin();
		 it != in.sphere_file().end();
		 it++ )
	{
		//SphereGenerator input(particleList, it->c_str());

		LOG4CXX_DEBUG(xmllogger, "reading sphere file \"" << it->c_str() << "\"");
		//input.input();
	}
	
	particles->add(particleList);


	// 3: element "output"
	const simulation_output_t& out = s->output();

	// 3.1: element "base_filename"
	string base_filename( out.base_filename() );
	LOG4CXX_DEBUG(xmllogger, "reading base_filename=\"" << base_filename << "\"");

	::particleOut = new ParticleOutput_VTK(*particles, base_filename);

	// 3.2: element "output_freq"
	::output_freq = out.output_freq();
	if( ::output_freq > 0 ) {
		LOG4CXX_DEBUG(xmllogger, "reading output_freq=" << ::output_freq);
	} else {
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for output_freq.");
		exit(1);
	}
	

	// create default position and velocity calculators
	xcalc = new PositionCalculator();
	vcalc = new VelocityCalculator();
}


