/*
 * ParticleContainer.cpp
 *
 *  Created on: 24.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleContainer.h"


/**
 * \brief Constructor for setting an initial particle list.
 * @initialParticleList ParticleList which is copied into the ParticleContainer.
 */
ParticleContainer::ParticleContainer(const std::list<Particle>& initialParticleList)
	: particleList(std::list<Particle>(initialParticleList.begin(), initialParticleList.end()))
{
}


/**
 * \brief Adds a particle to the particle container.
 * @P Particle to add.
 */
void ParticleContainer::add(Particle& P) {
	particleList.push_back(P);
}


/**
 * \brief Adds particles from a list to the particle container.
 * @list List of the particles to add.
 */
void ParticleContainer::add(std::list<Particle>& list)
{
	particleList.splice(particleList.end(), list);
}


/**
 * \brief Function for iterating over all particles.
 * @handler Object providing the compute function, which is called for every particle.
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
 *
 * @handler Object providing the compute function, which is called for every particle pair.
 *
 * This function iterates over all particle pairs and processes
 * each by calling the provided function.
 *
 * Force calculators use Newton's third law and therefore give
 * wrong outputs with this method. Use ParticleContainer::iterate_pairs_half instead.
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
 * @handler Object providing the compute function, which is called for every particle pair.
 *
 * This function uniquely iterates over all particle pairs and processes
 * each by calling the provided function. While `iterate_pairs` would process
 * both the particle pairs (a,b) and (b,a), this function only processes (a,b).
 *
 * This way the performance can be improved using Newton's third law.
 */
void ParticleContainer::iterate_pairs_half(PairHandler& handler)
{
	std::list<Particle>::iterator it_outer = particleList.begin();

	while(it_outer != particleList.end()) {
		std::list<Particle>::iterator it_inner = it_outer;
		it_inner++;

		while(it_inner != particleList.end()) {
			handler.compute(*it_outer, *it_inner);
			it_inner++;
		}

		it_outer++;
	}
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

