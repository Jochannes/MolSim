/*
 * MembraneContainer.h
 *
 *  Created on: 22.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef MEMBRANECONTAINER_H_
#define MEMBRANECONTAINER_H_

#include "ParticleContainer/ParticleContainer.h"
#include "ParticleContainer/SimpleContainer.h"
#include "ParticleContainer/CellContainer.h"
#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"

#include <list>
#include <vector>


/**
 * \brief Particle container for membrane simulation.
 *
 * This class is based on the linked cell container.
 * All particles are arranged on a grid and have their
 * neighbors stored using the Particle::neighbors member.
 * This container makes sure that the neighbors are
 * correctly set and updated if necessary.
 */
class MembraneContainer: public SimpleContainer {

public:
	/*MembraneContainer(const Vector<double, 3> domainSize, const double cutoff)
		: CellContainer(domainSize, cutoff, NULL)
	{ }*/
	MembraneContainer() {
	}

	void fill_grid(std::list<Particle>& list, int size_x, int size_y);

	//void update_cells();
};

#endif /* MEMBRANECONTAINER_H_ */
