/*
 * CellContainer.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef CELLCONTAINER_H_
#define CELLCONTAINER_H_

#include "ParticleContainer/ParticleContainer.h"
#include "ParticleContainer/SimpleContainer.h"
#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"
#include "handler/ForcePrepareHandler.h"

#include <list>

using namespace std;
using namespace utils;

//Forward declaration of unit test class
namespace unitTest {
class UTest_CellContainer;
}

/**
 * \brief Particle container for the linked-cell algorithm
 *
 */
class CellContainer: public ParticleContainer {
	friend unitTest::UTest_CellContainer;

private:
	SimpleContainer* cells; //!< Array with one SimpleContainer per cell, including the halo region.
	Vector<double, 3> domainSize; 	//!< Domain size in each dimension.
	Vector<int, 3> cellCount; //!< Number of cells in each dimension \f$ N_i \f$.
	int cellTotal;					//!< Total number of cells \f$ N \f$.
	double cutoff;					//!< Cutoff radius.
	int* haloInds;//!< Indices of all halo cells for fast and simple iteration.
	int* boundInds;	//!< Indices of all boundary cells for fast and simple iteration.
	int haloSize;					//!< Number of halo cells.
	int boundSize;					//!< Number of boundary cells.
	bool dim3;					//!< Stores if the domain is three dimensional.

	void setHaloBoundary();

public:
	CellContainer(const Vector<double, 3> domainSize, const double cutoff);
	CellContainer(const Vector<double, 3> domainSize, const double cutoff,
			list<Particle>& initialParticleList);

	Vector<int, 3> calc3Ind(int n);
	int calcInd(Vector<int, 3> n);
	int calcCell(Vector<double, 3> x);

	bool empty();
	int size();

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
