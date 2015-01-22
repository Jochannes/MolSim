/*
 * SimpleContainer.h
 *
 *  Created on: Nov 25, 2014
 *      Author: johannes
 */

#ifndef SIMPLECONTAINER_H_
#define SIMPLECONTAINER_H_

#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"
#include "handler/ForcePrepareHandler.h"
#include "ParticleContainer/ParticleContainer.h"

#include <list>
#include <vector>

//Forward declaration of unit test class
namespace unitTest {
	class UTest_SimpleContainer;
}

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
class SimpleContainer: public ParticleContainer {
	friend class unitTest::UTest_SimpleContainer;

private:
	std::vector<Particle> particleList; //!< List with all particles.

public:
	SimpleContainer() :
			halo(false) {
	}
	SimpleContainer(const std::vector<Particle>& initialParticleList);

	~SimpleContainer() {
	}

	bool halo; //!< Sets this SimpleContainer as halo region (for the linked-cell algorithm).
	utils::Vector<int, 3> pos; //!< Position of this container.

	bool empty() {
		return particleList.empty();
	}

	int size() {
		return particleList.size();
	}

	Particle* add(Particle& P);
	void add(std::vector<Particle>& list);
	
	void reserve(unsigned int n) {
		particleList.reserve(n);
	}
	
	void remove(Particle& P);
	void remove_all();
	void remove_virtual();
	void remove_not_virtual();

	void prepare_forces();

	void iterate_all(ParticleHandler& handler);
	void iterate_pairs(PairHandler& handler);
	void iterate_pairs_half(PairHandler& handler);
	void iterate_partner(PairHandler& handler, ParticleContainer *partner);
};

#endif /* SIMPLECONTAINER_H_ */
