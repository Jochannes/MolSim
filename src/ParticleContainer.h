/*
 * ParticleContainer.h
 *
 *  Created on: 30.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"
#include "handler/ForcePrepareHandler.h"

#include <list>

/**
 * \brief A container for encapsulating the particle list.
 *
 * This class contains a list of all particles and
 * provides several functions for accessing them.
 *
 * Amongst others, it provides functions for iterating over
 * all particles and particle pairs and processing them using
 * a certain function.
 */
class ParticleContainer
{
private:
	std::list<Particle> particleList;

public:
	ParticleContainer(){
	}
	ParticleContainer(const std::list<Particle>& initialParticleList);

	~ParticleContainer() {
	}

	bool empty() const {
		return particleList.empty();
	}

	int size() const {
		return particleList.size();
	}

	void add(Particle& P);
	void add(std::list<Particle>& list);

	void prepare_forces();

	void iterate_all(ParticleHandler& handler);
	void iterate_pairs(PairHandler& handler);
	void iterate_pairs_half(PairHandler& handler);
};


#endif /* PARTICLECONTAINER_H_ */
