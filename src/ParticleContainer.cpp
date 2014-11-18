/*
 * ParticleContainer.cpp
 *
 *  Created on: 24.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleContainer.h"
#include "handler/PairHandlerConverter.h"

/**
 * \brief Constructor for setting an initial particle list.
 * @param initialParticleList ParticleList which is copied into the ParticleContainer.
 */
ParticleContainer::ParticleContainer(
		const std::list<Particle>& initialParticleList) :
		particleList(
				std::list<Particle>(initialParticleList.begin(),
						initialParticleList.end())) {
}

/**
 * \brief Adds a particle to the particle container.
 * @param p Particle to add.
 */
void ParticleContainer::add(Particle& p) {
	particleList.push_back(p);
}

/**
 * \brief Adds particles from a list to the particle container.
 * @param list List of the particles to add.
 */
void ParticleContainer::add(std::list<Particle>& list) {
	particleList.splice(particleList.end(), list);
}

/**
 * \brief Removes the particle from the particle container.
 * @param p Particle to remove.
 *
 * This function removes all particles that match the
 * properties of the specified particle from the container.
 */
void ParticleContainer::remove(Particle& p) {
	std::list<Particle>::iterator it = particleList.begin();

	while (it != particleList.end()) {
		if(*it == p){
			particleList.erase(it);
		}
		it++;
	}
}

/**
 * \brief Removes all particles from the particle container.
 */
void ParticleContainer::remove_all() {
	particleList.clear();
}

/**
 * \brief Function for iterating over all particles.
 * @param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles and processes
 * each by calling the provided function.
 */
void ParticleContainer::iterate_all(ParticleHandler& handler) {
	std::list<Particle>::iterator it = particleList.begin();

	while (it != particleList.end()) {
		handler.compute(*it);
		it++;
	}
}

/**
 * \brief Function for iterating over all particle pairs.
 *
 * @param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function iterates over all particle pairs and processes
 * each by calling the provided function.
 *
 * Force calculators use Newton's third law and therefore give
 * wrong outputs with this method. Use ParticleContainer::iterate_pairs_half instead.
 */
void ParticleContainer::iterate_pairs(PairHandler& handler) {
	std::list<Particle>::iterator it_outer = particleList.begin();

	while (it_outer != particleList.end()) {
		std::list<Particle>::iterator it_inner = particleList.begin();

		while (it_inner != particleList.end()) {
			if (it_outer != it_inner)
				handler.compute(*it_outer, *it_inner);

			it_inner++;
		}

		it_outer++;
	}
}

/**
 * \brief Function for iterating over unique particle pairs.
 * @param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function uniquely iterates over all particle pairs and processes
 * each by calling the provided function. While `iterate_pairs` would process
 * both the particle pairs (a,b) and (b,a), this function only processes (a,b).
 *
 * This way the performance can be improved using Newton's third law.
 */
void ParticleContainer::iterate_pairs_half(PairHandler& handler) {
	std::list<Particle>::iterator it_outer = particleList.begin();

	while (it_outer != particleList.end()) {
		std::list<Particle>::iterator it_inner = it_outer;
		it_inner++;

		while (it_inner != particleList.end()) {
			handler.compute(*it_outer, *it_inner);
			it_inner++;
		}

		it_outer++;
	}
}

/**
 * \brief Function for iterating over particle pairs from two particle containers.
 * @param handler Object providing the compute function, which is called for every particle pair.
 * @param partner Partner particle container.
 *
 * This function iterates over all particle pairs (a,b)
 * with particle a coming from this particle container
 * and particle b from the partner particle container.
 * It does so by using the pairHandlerConverter handler,
 * which converts a PairHandler into a ParticleHandler.
 */
void ParticleContainer::iterate_partner(PairHandler& handler, ParticleContainer *partner) {
	std::list<Particle>::iterator it = particleList.begin();
	PairHandlerConverter convHandler = PairHandlerConverter(&handler);

	while (it != particleList.end()) {
		convHandler.setPartner(&(*it));
		partner->iterate_all(convHandler);
		it++;
	}
}

/**
 * \brief Function for preparing the forces saved in the particle list.
 *
 * This function resets the forces calculated in the previous iteration step.
 * This preparation step is necessary for the calculation of the new forces.
 */
void ParticleContainer::prepare_forces() {
	iterate_all(*new ForcePrepareHandler());
}

