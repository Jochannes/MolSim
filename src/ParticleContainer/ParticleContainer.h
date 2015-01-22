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

#include <vector>

//Forward declaration of unit test class

/**
 * \brief Abstract class for defining an interface for particle storage.
 */
class ParticleContainer {
public:

	virtual ~ParticleContainer() {
	}

	virtual bool empty() = 0;

	virtual int size() = 0;

	virtual Particle* add(Particle& P) = 0;
	virtual void add(std::vector<Particle>& list) = 0;

	virtual void remove(Particle& P) = 0;

	virtual void prepare_forces() = 0;

	virtual void iterate_all(ParticleHandler& handler) = 0;
	virtual void iterate_pairs(PairHandler& handler) = 0;
	virtual void iterate_pairs_half(PairHandler& handler) = 0;
};

#endif /* PARTICLECONTAINER_H_ */
