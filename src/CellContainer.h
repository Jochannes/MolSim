/*
 * CellContainer.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef CELLCONTAINER_H_
#define CELLCONTAINER_H_

#include "ParticleContainer.h"
#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"
#include "handler/ForcePrepareHandler.h"

#include <list>

using namespace std;
using namespace utils;

/**
 * \brief Particle container for the linked-cell algorithm
 *
 */
class CellContainer : ParticleContainer {
private:
	ParticleContainer* cells; 		//!< Array with one ParticleContainer per cell, including the halo region.
	Vector<double, 3> domainSize; 	//!< Domain size in each dimension.
	Vector<int, 3> cellCount; 		//!< Number of cells in each dimension \f$ N_i \f$.
	double cutoff;					//!< Cutoff radius.

public:
	CellContainer(const Vector<double, 3> domainSize,
			const double cutoff);
	CellContainer(const Vector<double, 3> domainSize,
			const double cutoff, list<Particle>& initialParticleList);

	~CellContainer() {
		delete(cells);
	}

	Vector<int, 3> calc3Ind(int n);
	int calcInd(Vector<int, 3> n);
	int calcCell(Vector<double, 3> x);

	bool empty();
	int count();

	void add(Particle& p);
	void add(list<Particle>& list);

	void remove(Particle& p);
	void remove(Particle& p, int contInd);
	void remove_halo();

	void prepare_forces();

	void update_cells();

	void iterate_halo(ParticleHandler& handler);
	void iterate_boundary(ParticleHandler& handler);
	void iterate_all(ParticleHandler& handler);
	void iterate_pairs(PairHandler& handler);
	void iterate_pairs_half(PairHandler& handler);
};

#endif /* CELLCONTAINER_H_ */
