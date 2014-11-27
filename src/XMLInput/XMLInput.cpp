/*
 * XMLInput.cpp
 *
 *  Created on: 21.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "XMLInput.h"

#include "ParticleContainer/CellContainer.h"
#include "ParticleContainer/SimpleContainer.h"
#include "ParticleInput_FileReader.h"
#include "CuboidGenerator.h"
#include "ParticleOutput_VTK.h"
#include "handler/ForceCalculator_Gravity.h"
#include "handler/ForceCalculator_LennardJones.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "BoundaryCondition/Reflection.h"
#include "BoundaryCondition/Outflow.h"
#include "global.h"
#include "utils/Vector.h"
#include "simulation.h"

#include <log4cxx/logger.h>
#include <auto_ptr.h>
#include <list>
#include <string>

using namespace std;
using namespace log4cxx;
using namespace utils;


void XMLInput::ReadFile()
{
	LoggerPtr xmllogger(Logger::getLogger("MolSim.XMLInput"));

	LOG4CXX_INFO(xmllogger, "parsing XML-file \"" << xmlfilename << "\"");

	auto_ptr<simulation_t> s;

	// parse XML file and create data structures
	try {
		s = simulation(xmlfilename);
	}
	catch (const xml_schema::exception& e) {
		LOG4CXX_FATAL(xmllogger, "Error reading XML-file: " << e);
		exit(1);
	}
	

	// 1: element "parameter"
	const simulation_parameters_t& param = s->parameter();

	// 1.1: start_time
	this->start_time = param.start_time();
	LOG4CXX_DEBUG(xmllogger, "reading start_time=" << this->start_time);

	// 1.2: end_time
	this->end_time = param.end_time();
	LOG4CXX_DEBUG(xmllogger, "reading end_time=" << this->end_time);

	// 1.3: delta_t
	this->delta_t = param.delta_t();
	if( this->delta_t > 0 ) {
		LOG4CXX_DEBUG(xmllogger, "reading delta_t=" << this->delta_t);
	} else {
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for delta_t.");
		exit(1);
	}

	// 1.4: force-calculator
	const force_calculator_t& fc = param.force_calculator();
	
	// 1.4.1: type
	this->fc_type = fc.type();

	switch( this->fc_type) {
	case force_calculator_type_t::gravity: {
			LOG4CXX_DEBUG(xmllogger, "using gravity force calculator.");
		}
		break;

	case force_calculator_type_t::lennard_jones: {
			LOG4CXX_DEBUG(xmllogger, "using Lennard-Jones force calculator.");
			
			// 1.4.2: epsilon
			const force_calculator_t::epsilon_optional& epsilon = fc.epsilon();
			if (epsilon.present()) {
				this->epsilon = epsilon.get();
				LOG4CXX_DEBUG(xmllogger, "reading epsilon=" << this->epsilon);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no epsilon specified for force calculation");
				// using default value
			}
			
			// 1.4.3: sigma
			const force_calculator_t::sigma_optional& sigma = fc.sigma();
			if (sigma.present()) {
				this->sigma = sigma.get();
				LOG4CXX_DEBUG(xmllogger, "reading sigma=" << this->sigma);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no sigma specified for force calculation.");
				// using default value.
			}
		}
		break;
	
	default:
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for force calculator type!");
		exit(1);
	};


	// 1.5: simulation-mode
	const simulation_mode_t& sm = param.simulation_mode();
	
	// 1.4.1: type
	this->sm_type = sm.type();

	switch( this->sm_type ) {
	case simulation_mode_type_t::normal: {
			LOG4CXX_DEBUG(xmllogger, "using normal simulation mode.");
		}
		break;

	case simulation_mode_type_t::linked_cell: {
			LOG4CXX_DEBUG(xmllogger, "using Linked-Cell simulation mode.");
			
			// 1.4.2: cutoff_radius
			const simulation_mode_t::cutoff_radius_optional& cutoff_radius = sm.cutoff_radius();
			if (cutoff_radius.present()) {
				this->cutoff_radius = cutoff_radius.get();
				LOG4CXX_DEBUG(xmllogger, "reading cutoff_radius=" << this->cutoff_radius);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no cutoff_radius specified for Linked-Cell-mode.");
				// using default value.
			}
			
			// 1.4.3: domain_size_x
			const simulation_mode_t::domain_size_x_optional& domain_size_x = sm.domain_size_x();
			if (domain_size_x.present()) {
				this->domain_size[0] = domain_size_x.get();
				LOG4CXX_DEBUG(xmllogger, "reading domain_size_x=" << this->domain_size[0]);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no domain_size_x specified for Linked-Cell-mode.");
				// using default value.
			}
			
			// 1.4.4: domain_size_y
			const simulation_mode_t::domain_size_y_optional& domain_size_y = sm.domain_size_y();
			if (domain_size_y.present()) {
				this->domain_size[1] = domain_size_y.get();
				LOG4CXX_DEBUG(xmllogger, "reading domain_size_y=" << this->domain_size[1]);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no domain_size_y specified for Linked-Cell-mode.");
				// using default value.
			}

			// 1.4.5: domain_size_z
			const simulation_mode_t::domain_size_z_optional& domain_size_z = sm.domain_size_z();
			if (domain_size_z.present()) {
				this->domain_size[2] = domain_size_z.get();
				LOG4CXX_DEBUG(xmllogger, "reading domain_size_z=" << this->domain_size[2]);
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no domain_size_z specified for Linked-Cell-mode.");
				// using default value.
			}

			// 1.4.6: boundary
			const simulation_mode_t::boundary_optional& boundary = sm.boundary();
			if (boundary.present()) {
				const boundary_t& b = boundary.get();

				this->boundary[0] = b.x_0();
				this->boundary[1] = b.x_max();
				this->boundary[2] = b.y_0();
				this->boundary[3] = b.y_max();
				this->boundary[4] = b.z_0();
				this->boundary[5] = b.z_max();
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no boundary conditions specified for Linked-Cell-mode.");
				// using default behaviour
			}
		}
		break;
	
	default:
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for simulation mode type!");
		exit(1);
	};

	// 2: element "input"
	const simulation_input_t& in = s->input();

	// 2.1: element "particle_file"
	this->particle_file.reserve( in.particle_file().size() );
	for( simulation_input_t::particle_file_const_iterator it = in.particle_file().begin();
		 it != in.particle_file().end();
		 it++ )
	{
		ParticleInput_FileReader fr(*it);
		this->particle_file.push_back(fr);

		LOG4CXX_DEBUG(xmllogger, "reading particle file " << fr.toString());
	}
	
	// 2.2: element "cuboid"
	this->cuboid.reserve( in.cuboid().size() );
	for( simulation_input_t::cuboid_const_iterator it = in.cuboid().begin();
		 it != in.cuboid().end();
		 it++ )
	{
		double corner_position[3] = {it->x1(), it->x2(), it->x3()};
		int    num_particles[3]   = {it->n1(), it->n2(), it->n3()};
		double distance           = it->h();
		double mass               = it->m();
		double velocity[3]        = {it->v1(), it->v2(), it->v3()};
		double brown_factor       = 0.1;

		CuboidGenerator c(corner_position, num_particles, distance, mass, velocity, brown_factor);
		this->cuboid.push_back(c);

		LOG4CXX_DEBUG(xmllogger, "reading cuboid " << c.toString());
	}
	
	// 2.3: element "sphere"
	this->sphere.reserve( in.sphere().size() );
	for( simulation_input_t::sphere_const_iterator it = in.sphere().begin();
		 it != in.sphere().end();
		 it++ )
	{
		double center_position[3] = {it->x1(), it->x2(), it->x3()};
		int    radius             = it->r();
		double distance           = it->h();
		double mass               = it->m();
		double velocity[3]        = {it->v1(), it->v2(), it->v3()};
		double brown_factor       = 0.1;

		SphereGenerator s(center_position, radius, distance, mass, velocity, brown_factor);
		this->sphere.push_back(s);

		LOG4CXX_DEBUG(xmllogger, "reading sphere " << s.toString());
	}
	

	// 3: element "output"
	const simulation_output_t& out = s->output();

	// 3.1: element "base_filename"
	this->base_filename = out.base_filename();
	LOG4CXX_DEBUG(xmllogger, "reading base_filename=\"" << this->base_filename << "\"");

	// 3.2: element "output_freq"
	this->output_freq = out.output_freq();
	if( this->output_freq > 0 ) {
		LOG4CXX_DEBUG(xmllogger, "reading output_freq=" << this->output_freq);
	} else {
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for output_freq.");
		exit(1);
	}
}


void XMLInput::configureApplication()
{
	// parameter
	::start_time = this->start_time;
	::end_time   = this->end_time;
	::delta_t    = this->delta_t;

	switch (this->fc_type) {
	case force_calculator_type_t::gravity:
		::fcalc = new ForceCalculator_Gravity();
		break;

	case force_calculator_type_t::lennard_jones:
		ForceCalculator_LennardJones::epsilon = this->epsilon;
		ForceCalculator_LennardJones::sigma   = this->sigma;
		::fcalc = new ForceCalculator_LennardJones();
		break;
	}

	switch (this->sm_type) {
	case simulation_mode_type_t::normal:
		::particles = new SimpleContainer();
		break;

	case simulation_mode_type_t::linked_cell:
		CellContainer *tmp_particles = new CellContainer(this->domain_size, this->cutoff_radius);

		// set boundary conditions
		for(int i=0; i<6; i++) {
			switch (this->boundary[i]) {
			case boundary_type_t::outflow:
				tmp_particles->boundConds[i] = new Outflow(i);
				break;

			case boundary_type_t::reflect:
				tmp_particles->boundConds[i] = new Reflection(tmp_particles, i);
				break;
			}
		}

		::particles = tmp_particles;
		break;
	}


	// input
	list<Particle> particleList;

	for( vector<ParticleInput_FileReader>::iterator it = this->particle_file.begin();
		 it != this->particle_file.end();
		 it++ )
	{
		it->input(particleList);
	}

	for( vector<CuboidGenerator>::iterator it = this->cuboid.begin();
		 it != this->cuboid.end();
		 it++ )
	{
		it->input(particleList);
	}

	for( vector<SphereGenerator>::iterator it = this->sphere.begin();
		 it != this->sphere.end();
		 it++ )
	{
		it->input(particleList);
	}

	::particles->add(particleList);


	// output
	::particleOut = new ParticleOutput_VTK(*::particles, this->base_filename);
	::output_freq = this->output_freq;


	// create default position and velocity calculators
	::xcalc = new PositionCalculator();
	::vcalc = new VelocityCalculator();
}

