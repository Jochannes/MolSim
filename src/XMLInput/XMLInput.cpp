/*
 * XMLInput.cpp
 *
 *  Created on: 21.11.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "XMLInput.h"

#include "ParticleContainer/CellContainer.h"
#include "ParticleContainer/SimpleContainer.h"
#include "ParticleContainer/MembraneContainer.h"
#include "ParticleFileReader.h"
#include "CuboidGenerator.h"
#include "ParticleOutput_VTK.h"
#include "ResultOutput.h"
#include "handler/PositionCalculator.h"
#include "handler/VelocityCalculator.h"
#include "BoundaryCondition/Outflow.h"
#include "BoundaryCondition/Reflection.h"
#include "BoundaryCondition/Periodic.h"
#include "Thermostat.h"
#include "VelDenProfile.h"
#include "global.h"
#include "utils/Vector.h"
#include "simulation.h"

#include <log4cxx/logger.h>
#include <auto_ptr.h>
#include <list>
#include <vector>
#include <string>
#include <sstream>

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

	// 1.4: simulation-mode
	const simulation_mode_t& sm = param.simulation_mode();
	
	// 1.4.1: type
	this->sm_type = sm.type();

	switch( this->sm_type ) {
	case simulation_mode_type_t::normal: {
			LOG4CXX_DEBUG(xmllogger, "using normal simulation mode.");
		}
		break;

	case simulation_mode_type_t::membrane: {
			LOG4CXX_DEBUG(xmllogger, "using Membrane simulation mode.");

		}
		// no break;

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

				stringstream str;
				str << "[ ";
				for(int i=0; i<6; i++) {
					switch(this->boundary[i]) {
					case boundary_type_t::outflow:
						str << "outflow ";
						break;
					case boundary_type_t::reflect:
						str << "reflect ";
						break;
					case boundary_type_t::periodic:
						str << "periodic ";
						break;
					}
				}
				str << "]";

				LOG4CXX_DEBUG(xmllogger, "reading boundary conditions for Linked-Cell-mode: " << str.str());
			}
			else {
				LOG4CXX_DEBUG(xmllogger, "no boundary conditions specified for Linked-Cell-mode.");
				// using default behavior
			}
		}
		break;
	
	default:
		LOG4CXX_FATAL(xmllogger, "Error! Invalid value for simulation mode type!");
		exit(1);
	};

	// 1.5: thermostat
	const simulation_parameters_t::thermostat_optional therm = param.thermostat();
	if (therm.present()) {
		this->dim = therm.get().dim();
		if (this->dim < 2  ||  this->dim > 3) {
			LOG4CXX_FATAL(xmllogger, "Error! Invalid value for thermostat's \"dim\".");
			exit(1);
		}

		this->init_temp = therm.get().init_temp();

		this->steps = therm.get().steps();
		if (this->steps <= 0) {
			LOG4CXX_FATAL(xmllogger, "Error! Invalid value for thermostat's \"steps\".");
			exit(1);
		}

		if( therm.get().apply_brown().present() ) {
			this->applyBrown = therm.get().apply_brown().get();
		}

		if( therm.get().direction().present() ) {
			this->therm_direction = therm.get().direction().get();
		}

		if( therm.get().type().present() ) {
			this->therm_type = therm.get().type().get();
		}

		if ( therm.get().target_temp().present() &&
			 therm.get().delta_temp().present() &&
			 therm.get().steps_changetemp().present() )
		{
			this->target_temp      = therm.get().target_temp().get();
			this->delta_temp       = therm.get().delta_temp().get();

			this->steps_changetemp = therm.get().steps_changetemp().get();
			if (this->steps_changetemp <= 0) {
				LOG4CXX_FATAL(xmllogger, "Error! Invalid value for thermostat's \"steps_changetemp\".");
				exit(1);
			}

			LOG4CXX_DEBUG(xmllogger, "using variable thermostat: dim=" << this->dim <<
					"; init_temp=" << this->init_temp << "; steps=" << this->steps <<
					"; target_temp=" << this->target_temp << "; delta_temp=" << this->delta_temp <<
					"; steps_changetemp=" << this->steps_changetemp <<
					"; applyBrown=" << (applyBrown ? "true" : "false") <<
					"; type=" << this->therm_type << "; direction=" << this->therm_direction );
		}
		else {
			LOG4CXX_DEBUG(xmllogger, "using constant thermostat: dim=" << this->dim <<
					"; init_temp=" << this->init_temp << "; steps=" << this->steps <<
					"; applyBrown=" << (applyBrown ? "true" : "false") <<
					"; type=" << this->therm_type << "; direction=" << this->therm_direction );
		}
	}

	// 1.6: thermodyn_stats
	const simulation_parameters_t::thermodyn_stats_optional thdyn = param.thermodyn_stats();
	this->thdyn_use = thdyn.present();
	if (thdyn.present()) {
		this->thdyn_freq = thdyn.get().freq();
		this->thdyn_avgover = thdyn.get().avgover();
		this->thdyn_dr = thdyn.get().dr();
		this->thdyn_maxrad = thdyn.get().maxrad();
		this->thdyn_varfile = thdyn.get().varfile();
		this->thdyn_rdffile = thdyn.get().rdffile();

		LOG4CXX_DEBUG(xmllogger, "calculating thermodynamic statistics: freq=" << this->thdyn_freq <<
				"; avgover=" << this->thdyn_avgover << "; dr=" << this->thdyn_dr <<
				"; maxrad=" << this->thdyn_maxrad << "; varfile='" << this->thdyn_varfile << "'; rdffile='" << this->thdyn_rdffile << "'");
	}

	// 1.7: fixed
	const simulation_parameters_t::fixed_optional fixed = param.fixed();
	if (fixed.present()) {
		this->fixed_count = fixed.get().size();

		if( this->fixed_count > 0 ) {
			this->fixed_types = new int[this->fixed_count];

			LOG4CXX_DEBUG(xmllogger, "using " << this->fixed_count << " fixed types.");

			int i = 0;
			for( fixed_t::const_iterator it = fixed.get().begin();
				 it != fixed.get().end();
			 	 it++ )
			{
				LOG4CXX_DEBUG(xmllogger, *it);

				this->fixed_types[i] = *it;
				i++;
			}
		}
	}

	// 1.8: VelDenProfile
	const simulation_parameters_t::velocity_density_profile_optional vdp = param.velocity_density_profile();
	if( vdp.present() ) {
		this->vlp_use     = true;
		this->vlp_x_start = vdp.get().x_start();
		this->vlp_x_end   = vdp.get().x_end();
		this->vlp_x_count = vdp.get().x_count();
		this->vlp_vfile   = vdp.get().vfile();
		this->vlp_dfile   = vdp.get().dfile();
		this->vlp_freq	  = vdp.get().freq();

		LOG4CXX_DEBUG(xmllogger, "using velocity-density-profiling:" <<
				"x_start=" << this->vlp_x_start <<
				", x_end=" << this->vlp_x_end <<
				", x_count=" << this->vlp_x_count <<
				", vfile=" << this->vlp_vfile <<
				", dfile=" << this->vlp_dfile <<
				", freq=" << this->vlp_freq );
	}

	// 2: element "force-calculator"
	const simulation_force_calculator_t& fc = s->force_calculator();
	forceCalcCnt = 0;

	// 2.1: element "lennard_jones"
	forceCalcCnt += fc.lennard_jones().size();
	for( simulation_force_calculator_t::lennard_jones_const_iterator it = fc.lennard_jones().begin();
		 it != fc.lennard_jones().end();
		 it++ )
	{
		if( it->cutoff_factor().present() ) {
			const double cutoff_factor = it->cutoff_factor().get();
			this->lennard_jones.push_back(ForceCalculator_LennardJones(cutoff_factor));

			LOG4CXX_DEBUG(xmllogger, "using Lennard-Jones force calculator with cutoff radius, cutoff_factor=" << cutoff_factor << ".");
		}
		else {
			this->lennard_jones.push_back(ForceCalculator_LennardJones());

			LOG4CXX_DEBUG(xmllogger, "using Lennard-Jones force calculator without cutoff.");
		}
	}

	// 2.2: element "lj_smoothed"
	forceCalcCnt += fc.lj_smoothed().size();
	for( simulation_force_calculator_t::lj_smoothed_const_iterator it = fc.lj_smoothed().begin();
		 it != fc.lj_smoothed().end();
		 it++ )
	{
		const double cutoff_factor = it->cutoff_factor();
		const double rl = it->rl();
		this->lj_smoothed.push_back(ForceCalculator_LJ_smoothed(cutoff_factor, rl));

		LOG4CXX_DEBUG(xmllogger, "using smoothed Lennard-Jones force calculator with cutoff radius, cutoff_factor=" << cutoff_factor << ", rl=" << rl << ".");
	}

	// 2.3: element "gravity"
	forceCalcCnt += fc.gravity().size();
	this->gravity.reserve( fc.gravity().size() );
	for( simulation_force_calculator_t::gravity_const_iterator it = fc.gravity().begin();
		 it != fc.gravity().end();
		 it++ )
	{
		double g_grav = it->g_grav();
		unsigned int direction = 1;	// y axis
		int type = -1;

		if( it->direction().present() ) {
			switch( it->direction().get() )
			{
			case direction_t::x:
				direction = 0;
				break;

			case direction_t::y:
				direction = 1;
				break;

			case direction_t::z:
				direction = 2;
				break;
			}
		}

		if( it->type().present() ) {
			type = it->type().get();
		}

		this->gravity.push_back(ForceCalculator_Gravity(g_grav, direction));

		LOG4CXX_DEBUG(xmllogger, "using gravity force calculator, g_grav=" << g_grav << ", direction=" << direction << ", type=" << type << ".");
	}

	// 2.4: element "harmonic"
	forceCalcCnt += fc.harmonic().size();
	this->harmonic.reserve( fc.harmonic().size() );
	for( simulation_force_calculator_t::harmonic_const_iterator it = fc.harmonic().begin();
		 it != fc.harmonic().end();
		 it++ )
	{
		double k = it->k();
		double r = it->r();
		this->harmonic.push_back(ForceCalculator_Harmonic(k ,r));

		LOG4CXX_DEBUG(xmllogger, "using harmonic force calculator, k=" << k << ", r=" << r << ".");
	}

	// 2.5: element "constant"
	this->constant_force.reserve( fc.constant().size() );
	for( simulation_force_calculator_t::constant_const_iterator it = fc.constant().begin();
		 it != fc.constant().end();
		 it++ )
	{
		int particle_type = it->type();
		double force[3] = { it->force_x(), it->force_y(), it->force_z() };
		double start_time = 0.0;
		double end_time = DBL_MAX;

		if( it->start_time().present() ) {
			start_time = it->start_time().get();
		}
		if( it->end_time().present() ) {
			end_time = it->end_time().get();
		}

		this->constant_force.push_back(ForceCalculator_Constant(force, particle_type, start_time, end_time));

		LOG4CXX_DEBUG(xmllogger, "using constant force calculator, type=" <<
				particle_type << ", force=" << force << ", start_time=" <<
				start_time << ", end_time=" << end_time << ".");
	}


	// 3: element "input"
	const simulation_input_t& in = s->input();

	// 3.1: element "particle_file"
	this->particle_file.reserve( in.particle_file().size() );
	for( simulation_input_t::particle_file_const_iterator it = in.particle_file().begin();
		 it != in.particle_file().end();
		 it++ )
	{
		ParticleFileReader fr(*it);
		this->particle_file.push_back(fr);

		LOG4CXX_DEBUG(xmllogger, "reading particle file " << fr.toString());
	}
	
	// 3.2: element "cuboid"
	this->cuboid.reserve( in.cuboid().size() );
	for( simulation_input_t::cuboid_const_iterator it = in.cuboid().begin();
		 it != in.cuboid().end();
		 it++ )
	{
		double corner_position[3] = {it->x1(), it->x2(), it->x3()};
		int    num_particles[3]   = {it->n1(), it->n2(), it->n3()};
		double distance           = it->h();
		double mass               = it->m();
		double epsilon            = it->epsilon();
		double sigma              = it->sigma();
		int type	              = it->type();
		double velocity[3]        = {it->v1(), it->v2(), it->v3()};

		CuboidGenerator c(corner_position, num_particles, distance, mass, velocity, type, epsilon, sigma);
		this->cuboid.push_back(c);

		LOG4CXX_DEBUG(xmllogger, "reading cuboid " << c.toString());
	}
	
	// 3.3: element "sphere"
	this->sphere.reserve( in.sphere().size() );
	for( simulation_input_t::sphere_const_iterator it = in.sphere().begin();
		 it != in.sphere().end();
		 it++ )
	{
		double center_position[3] = {it->x1(), it->x2(), it->x3()};
		int    radius             = it->r();
		double distance           = it->h();
		double mass               = it->m();
		double epsilon            = it->epsilon();
		double sigma              = it->sigma();
		int type	              = it->type();
		double velocity[3]        = {it->v1(), it->v2(), it->v3()};
		bool   use3D              = false;

		SphereGenerator s(center_position, radius, distance, mass, velocity, use3D, type, epsilon, sigma);
		this->sphere.push_back(s);

		LOG4CXX_DEBUG(xmllogger, "reading sphere " << s.toString());
	}
	
	// 3.4: element "membrane"
	this->membrane.reserve( in.membrane().size() );
	for( simulation_input_t::membrane_const_iterator it = in.membrane().begin();
		 it != in.membrane().end();
		 it++ )
	{
		double corner_position[3] = {it->x1(), it->x2(), it->x3()};
		int    num_particles[3]   = {it->n1(), it->n2(), it->n3()};
		double distance           = it->h();
		double mass               = it->m();
		double epsilon            = it->epsilon();
		double sigma              = it->sigma();
		int type	              = it->type();
		double velocity[3]        = {it->v1(), it->v2(), it->v3()};

		int mark_type = 0;
		int mark_x = -1;
		int mark_y = -1;

		if( it->mark_type().present() ) {
			mark_type = it->mark_type().get();

			if( it->mark_x().present() && it->mark_y().present() ) {
				mark_x = it->mark_x().get();
				mark_y = it->mark_y().get();
			} else {
				LOG4CXX_FATAL(xmllogger, "Error reading membrane! Marking not fully specified.");
				exit(1);
			}
		}

		MembraneGenerator m(corner_position, num_particles, distance, mass, velocity, type, epsilon, sigma, mark_type, mark_x, mark_y);
		this->membrane.push_back(m);

		LOG4CXX_DEBUG(xmllogger, "reading membrane " << m.toString());
	}

	// 4: element "output"
	const simulation_output_t& out = s->output();

	// 4.1: element "iteration"
	if( out.iteration().present() ) {
		const iteration_output_t out_it = out.iteration().get();

		this->base_filename = out_it.base_filename();

		this->output_freq   = out_it.output_freq();
		if( this->output_freq <= 0 ) {
			LOG4CXX_FATAL(xmllogger, "Error! In iteration output: invalid value for output_freq.");
			exit(1);
		}

		LOG4CXX_DEBUG(xmllogger, "reading iteration output: base_filename=\"" << this->base_filename <<
									"\"; output_freq=" << this->output_freq );
	}

	// 4.2: element "result"
	if( out.result().present() ) {
		const result_output_t out_res = out.result().get();

		this->res_filename = out_res.filename();

		LOG4CXX_DEBUG(xmllogger, "reading result output: filename=\"" << this->res_filename << "\"");
	}
}


void XMLInput::configureApplication()
{
	// parameter
	::start_time = this->start_time;
	::end_time   = this->end_time;
	::delta_t    = this->delta_t;

	switch (this->sm_type) {
	case simulation_mode_type_t::normal: {
		::particles = new SimpleContainer();
		}
		break;

	case simulation_mode_type_t::membrane: {
		MembraneContainer *tmp_mparticles = new MembraneContainer();

		// add particles
		for( vector<MembraneGenerator>::iterator it = this->membrane.begin();
			 it != this->membrane.end();
			 it++ )
		{
			std::list<Particle> particleListMem;
			it->input(particleListMem);
			cout << "a" << endl;
			tmp_mparticles->fill_grid(particleListMem, it->getSizeX(), it->getSizeY());
			cout << "b" << endl;
		}

		/*// set boundary conditions
		for(int i=0; i<6; i++) {
			switch (this->boundary[i]) {
			case boundary_type_t::outflow:
				tmp_mparticles->boundConds[i] = new Outflow(i);
				break;

			case boundary_type_t::reflect:
				tmp_mparticles->boundConds[i] = new Reflection(tmp_mparticles, i);
				break;

			case boundary_type_t::periodic:
				tmp_mparticles->boundConds[i] = new Periodic(tmp_mparticles, i);
				break;
			}
		}*/

		::particles = tmp_mparticles;
		}
		break;

	case simulation_mode_type_t::linked_cell: {
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

			case boundary_type_t::periodic:
				tmp_particles->boundConds[i] = new Periodic(tmp_particles, i);
				break;
			}
		}

		::particles = tmp_particles;
		}
		break;
	}


	//Force calculators
	::numForceCalcs = this->forceCalcCnt;
	fcalcs = new ForceCalculator*[this->forceCalcCnt];
	int i = 0;
	for( vector<ForceCalculator_LennardJones>::iterator it = this->lennard_jones.begin();
		 it != this->lennard_jones.end();
		 it++ )
	{
		::fcalcs[i] = new ForceCalculator_LennardJones(it->cutoff_factor);
		i++;
	}
	for( vector<ForceCalculator_LJ_smoothed>::iterator it = this->lj_smoothed.begin();
		 it != this->lj_smoothed.end();
		 it++ )
	{
		::fcalcs[i] = new ForceCalculator_LJ_smoothed(it->cutoff_factor, it->rl);
		i++;
	}
	for( vector<ForceCalculator_Gravity>::iterator it = this->gravity.begin();
		 it != this->gravity.end();
		 it++ )
	{
		::fcalcs[i] = new ForceCalculator_Gravity(*it);
		i++;
	}
	for( vector<ForceCalculator_Harmonic>::iterator it = this->harmonic.begin();
		 it != this->harmonic.end();
		 it++ )
	{
		::fcalcs[i] = new ForceCalculator_Harmonic(*it);
		i++;
	}

	::numTimedForceCalcs = this->constant_force.size();
	::tfcalcs = new ForceCalculator_Constant*[::numTimedForceCalcs];
	i = 0;
	for( vector<ForceCalculator_Constant>::iterator it = this->constant_force.begin();
		 it != this->constant_force.end();
		 it++ )
	{
		::tfcalcs[i] = new ForceCalculator_Constant(*it);
		i++;
	}


	// input
	std::list<Particle> particleList;

	for( vector<ParticleFileReader>::iterator it = this->particle_file.begin();
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

	//Add particles
	for( list<Particle>::iterator it = particleList.begin();
		 it != particleList.end();
		 it++ )
	{
		::particles->add(*it);
	}

	// Thermostat
	if (this->dim > 0) {
		if (this->delta_temp == 0.0) {		// use a constant temperature
			::thermostat = new Thermostat(*::particles, this->dim, this->init_temp, this->steps,
											this->applyBrown, this->therm_type, this->therm_direction);
		}
		else {								// use a variable temperature
			::thermostat = new Thermostat(*::particles, this->dim, this->init_temp, this->steps,
											this->target_temp, this->delta_temp, this->steps_changetemp,
											this->applyBrown, this->therm_type, this->therm_direction);
		}
	}
	else {
		::thermostat = NULL;
	}

	// ThermoDynStats
	if(this->thdyn_use) {
		::thdynStats = new ThermoDynStats(this->thdyn_freq, this->thdyn_avgover, this->thdyn_dr, this->thdyn_maxrad, this->thdyn_varfile, this->thdyn_rdffile);
	} else {
		::thdynStats = NULL;
	}

	// VelDenProfile
	if( this->vlp_use ) {
		::VelDenPr = new VelDenProfile(::particles, this->vlp_x_count, this->vlp_x_start, this->vlp_x_end, this->vlp_vfile, this->vlp_dfile, this->vlp_freq);
	}

	// output
	if( !this->base_filename.empty() ) {
		::particleOut = new ParticleOutput_VTK(*::particles, this->base_filename);
		::output_freq = this->output_freq;
	}
	if( !this->res_filename.empty() ) {
		::resultOut = new ResultOutput(*::particles, this->res_filename);
	}

	// create default position and velocity calculators
	::xcalc = new PositionCalculator(this->fixed_count, this->fixed_types);
	::vcalc = new VelocityCalculator();
}

