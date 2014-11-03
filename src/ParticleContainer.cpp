/*
 * ParticleContainer.cpp
 *
 *  Created on: 24.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleContainer.h"

#include <list>

/**
 * \brief Function for iterating over all particles.
 * \param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles and processes
 * each by calling the provided function.
 */
void ParticleContainer::iterate_all(ParticleHandler& handler)
{
	std::list<Particle>::iterator it = particleList.begin();

	while(it != particleList.end()) {
		handler.compute(*it);
		it++;
	}
}



/**
 * \brief Function for iterating over all particle pairs.
 * \param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function iterates over all particle pairs and processes
 * each by calling the provided function.
 */
void ParticleContainer::iterate_pairs(PairHandler& handler)
{
	std::list<Particle>::iterator it_outer = particleList.begin();

	while(it_outer != particleList.end()) {
		std::list<Particle>::iterator it_inner = particleList.begin();

		while(it_inner != particleList.end()) {
			if( it_outer != it_inner )
				handler.compute(*it_outer, *it_inner);

			it_inner++;
		}

		it_outer++;
	}
}



/**
 * \brief Function for iterating over unique particle pairs.
 * \param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function uniquely iterates over all particle pairs and processes
 * each by calling the provided function. While `iterate_pairs` would process
 * both the particle pairs (a,b) and (b,a), this function only processes (a,b).
 *
 * This way the performance can be improved using Newton's third law.
 */
void ParticleContainer::iterate_pairs_half(PairHandler& handler)
{
	// TODO: implement cost saving iteration method for force calculation (use Newton's third law)
}


/**
 * \brief Function for preparing the forces saved in the particle list.
 *
 * This function resets the forces calculated in the previous iteration step.
 * This preparation step is necessary for the calculation of the new forces.
 */
void ParticleContainer::prepare_forces()
{
	iterate_all( *new ForcePrepareHandler() );
}

